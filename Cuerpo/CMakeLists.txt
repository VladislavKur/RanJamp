target_sources(libClases PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/Cuerpo.cpp"
)

#Y donde se encuentran los .h
target_include_directories(libClases PUBLIC 
"${CMAKE_CURRENT_SOURCE_DIR}"
)
