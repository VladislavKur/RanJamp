target_sources(libClases PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/Juego.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Manejador.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Estado.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Transicion.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Final.cpp"
)

#Y donde se encuentran los .h
target_include_directories(libClases PUBLIC 
"${CMAKE_CURRENT_SOURCE_DIR}"
)
