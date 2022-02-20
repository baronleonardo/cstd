set(target cstd)

add_library(${target}
    def.h
    utils.h
    config.h
##### print #####
    print.h
    src/print.c
##### allocators #####
    # arena
    allocator/arena.h
    src/allocator/arena.c
    src/allocator/__arena__.h
)

target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})