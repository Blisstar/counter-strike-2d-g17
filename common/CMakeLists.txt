# Buscar todos los .cpp y .hpp desde este nivel
file(GLOB_RECURSE CPP_FILES CONFIGURE_DEPENDS *.cpp)
file(GLOB_RECURSE HPP_FILES CONFIGURE_DEPENDS *.hpp)

# Agregar los archivos fuente
target_sources(cs2d_common
    PRIVATE ${CPP_FILES}
    PUBLIC  ${HPP_FILES}
)
