target_sources(cs2d_common
    PRIVATE
    # .cpp files
    *.cpp
    PUBLIC
    # .h files
    *.h
)

include(
    PUBLIC
    defs.h
    thread.h
)
