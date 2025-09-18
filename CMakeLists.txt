cmake_minimum_required(VERSION 3.20)
project(NoLibC C)

set(CMAKE_C_STANDARD 23)

add_executable(NoLibC main.c
        nolibc/nolibc.c
        nolibc/nolibc.h
        nolibc/priv_syscall.c
        nolibc/priv_syscall.h
        nolibc/types.h)
target_compile_options(NoLibC PRIVATE
        -fno-stack-protector
        -fno-builtin
)
target_link_options(NoLibC PRIVATE
        -nostdlib
        -nodefaultlibs
        -fno-builtin
        -fno-stack-protector
)