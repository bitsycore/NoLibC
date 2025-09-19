cmake_minimum_required(VERSION 3.20)
project(NoLibC C)

set(CMAKE_C_STANDARD 23)

add_executable(testlibc testlibc/main.c)

add_executable(NoLibC
        main.c
        nolibc.h
        nolibc/string.c
        nolibc/syscall.c
        nolibc/format.c
        nolibc/priv_nolibc.h
)

target_compile_options(NoLibC PRIVATE
        -fno-builtin
        -fno-stack-protector
        -nostdinc
)

target_link_options(NoLibC PRIVATE
        -fno-builtin
        -fno-stack-protector
        -nostdlib
        -nodefaultlibs
)