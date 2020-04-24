cmake_minimum_required(VERSION 3.1)
project(ranJamp)

#Añadir tantos subdirectorios como se necesiten
#En cada subdirectorio debe haber un fichero CMakeLists.txt
#Habitualmente cada subdirectorio determinará una libreria 


add_library(libClases STATIC)
add_subdirectory(Player)
add_subdirectory(Bullet)
add_subdirectory(Animacion)
add_subdirectory(Enemigos)
add_subdirectory(Mundo)
add_subdirectory(Motor)
add_subdirectory(Juego)
add_subdirectory(Objeto)
add_subdirectory(Texto)
add_subdirectory(Menu)
add_subdirectory(Hud)
add_subdirectory(Musica)
add_subdirectory(Cuerpo)

#Opciones a pasar al compilador de C++
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall -Wextra")
#Se desea generar un ejecutable, se especifica donde está el main
#y ficheros que aporten código que no sean librerias o subcarpetas 

add_executable(ranJamp main.cpp)
add_executable(pajarraco pajarraco.cpp)


#Añadir todos los objetos (ficheros o) que requiera el ejecutable. 
#Habitualmente todas las librerias definidas mediante subcarpetas
#aportaran código

target_link_libraries(ranJamp libClases)
target_link_libraries(pajarraco libClases)

  

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
#Para usar SFML
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(ranJamp ${SFML_LIBRARIES})
    target_link_libraries(pajarraco ${SFML_LIBRARIES})
   
endif()
