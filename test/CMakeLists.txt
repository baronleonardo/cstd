include(CTest)

set(target test)

add_executable(${target}
    main.c
)

target_link_libraries(${target} cstd)