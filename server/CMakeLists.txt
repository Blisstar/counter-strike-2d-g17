# Buscar todos los .cpp y .hpp desde este nivel
file(GLOB_RECURSE CPP_FILES CONFIGURE_DEPENDS *.cpp)
file(GLOB_RECURSE HPP_FILES CONFIGURE_DEPENDS *.hpp)

# Agregar los archivos fuente
target_sources(cs2d_server
    PRIVATE ${CPP_FILES}
    PUBLIC  ${HPP_FILES}
)

# Incluir desde esta misma carpeta (src/)
target_include_directories(cs2d_server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

