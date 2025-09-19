cmake_minimum_required(VERSION 3.20)
project(NoLibC C)

set(CMAKE_C_STANDARD 23)

add_executable(testlibc testlibc/main.c)

add_executable(NoLibC main.c
        nolibc/string.c
        nolibc.h
        nolibc/syscall.c
        nolibc/priv_nolibc.h
        nolibc/format.c
)
target_compile_options(NoLibC PRIVATE
        -fno-stack-protector
        -fno-builtin
        -fno-builtin-memset
        -nostdinc
)
target_link_options(NoLibC PRIVATE
        -nostdlib
        -nodefaultlibs
        -fno-builtin
        -nostdinc
        -fno-stack-protector
)