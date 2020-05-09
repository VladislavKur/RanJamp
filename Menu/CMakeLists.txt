target_sources(libClases PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/menu.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/menu_inicial.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/menu_controles.cpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/menu_vol.cpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/menu_pausa.cpp"
)

#Y donde se encuentran los .h
target_include_directories(libClases PUBLIC 
"${CMAKE_CURRENT_SOURCE_DIR}"
)
