# Install script for directory: /home/magiic/Escritorio/RanJamp

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/magiic/Escritorio/RanJamp/build/Player/cmake_install.cmake")
  include("/home/magiic/Escritorio/RanJamp/build/Bullet/cmake_install.cmake")
  include("/home/magiic/Escritorio/RanJamp/build/Animacion/cmake_install.cmake")
  include("/home/magiic/Escritorio/RanJamp/build/Enemigos/cmake_install.cmake")
  include("/home/magiic/Escritorio/RanJamp/build/Mundo/cmake_install.cmake")
  include("/home/magiic/Escritorio/RanJamp/build/Motor/cmake_install.cmake")
  include("/home/magiic/Escritorio/RanJamp/build/Juego/cmake_install.cmake")
  include("/home/magiic/Escritorio/RanJamp/build/Objeto/cmake_install.cmake")
  include("/home/magiic/Escritorio/RanJamp/build/Texto/cmake_install.cmake")
  include("/home/magiic/Escritorio/RanJamp/build/Menu/cmake_install.cmake")
  include("/home/magiic/Escritorio/RanJamp/build/Hud/cmake_install.cmake")
  include("/home/magiic/Escritorio/RanJamp/build/Musica/cmake_install.cmake")
  include("/home/magiic/Escritorio/RanJamp/build/Bloque/cmake_install.cmake")
  include("/home/magiic/Escritorio/RanJamp/build/Textura/cmake_install.cmake")
  include("/home/magiic/Escritorio/RanJamp/build/Cuerpo/cmake_install.cmake")
  include("/home/magiic/Escritorio/RanJamp/build/Rectangulo/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/magiic/Escritorio/RanJamp/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
