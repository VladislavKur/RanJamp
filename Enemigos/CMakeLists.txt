#Especificar donde se encuentran los ficheros cpp a compilar
target_sources(libClases PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/centinela.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/murcielago.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/reptante.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/enemigo.cpp"
)

#Y donde se encuentran los .h
target_include_directories(libClases PUBLIC 
"${CMAKE_CURRENT_SOURCE_DIR}"
)

