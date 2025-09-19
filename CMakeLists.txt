cmake_minimum_required(VERSION 3.20)
project(NoLibC C)

set(CMAKE_C_STANDARD 23)

add_executable(NoLibC
        main.c
        nolibc/headers/nlc.h
        nolibc/string.c
        nolibc/syscall.c
        nolibc/print.c
        nolibc/_syscall.h
        nolibc/intrinsic.c
        nolibc/write_buffer.c
        nolibc/_write_buffer.h
        nolibc/headers/nlc_types.h
)

target_include_directories(
        NoLibC PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/nolibc/headers
)

target_compile_options(NoLibC PRIVATE
        -fno-builtin
        -fno-stack-protector
        -nostdinc
)

# Common options for all platforms
set(COMMON_LINK_OPTIONS
        -fno-builtin
        -fno-stack-protector
        -nostdlib
        -nodefaultlibs
)

if(APPLE)
    list(APPEND COMMON_LINK_OPTIONS -Wl,-lSystem)
endif()

target_link_options(NoLibC PRIVATE ${COMMON_LINK_OPTIONS})