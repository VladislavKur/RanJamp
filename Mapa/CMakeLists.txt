target_sources(libClases PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/mapa.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/tinystr.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/tinyxml.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/tinyxmlparser.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/tinyxmlerror.cpp"
)

#Y donde se encuentran los .h
target_include_directories(libClases PUBLIC 
"${CMAKE_CURRENT_SOURCE_DIR}"
)
