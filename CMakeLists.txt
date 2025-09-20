cmake_minimum_required(VERSION 3.20)
project(NoLibC C)
set(CMAKE_C_STANDARD 23)

# ===================================================================================
# MARK: COMMON OPTIONS
# ===================================================================================

set(COMMON_LINK_OPTIONS
        -fno-builtin
        -fno-stack-protector
        -nostdlib
        -nodefaultlibs
)

if(APPLE)
    list(APPEND COMMON_LINK_OPTIONS -Wl,-lSystem)
endif()

set(COMMON_COMPILE_OPTIONS
        -fno-builtin
        -fno-stack-protector
        -nostdinc
)

# ===================================================================================
# MARK: NOLIBC
# ===================================================================================

add_library(NoLibC
        nolibc/public/nlc.h
        nolibc/string.c
        nolibc/syscall.c
        nolibc/print.c
        nolibc/_syscall.h
        nolibc/intrinsic.c
        nolibc/write_buffer.c
        nolibc/_write_buffer.h
        nolibc/public/nlc_types.h
        nolibc/memory.c
        nolibc/_system.h
        nolibc/system.c
        nolibc/arena.c
)

target_include_directories(
        NoLibC PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/nolibc/public
)

target_compile_options(NoLibC PUBLIC ${COMMON_COMPILE_OPTIONS})
target_link_options(NoLibC PUBLIC ${COMMON_LINK_OPTIONS})

# ===================================================================================
# MARK: NOLIBC_Test
# ===================================================================================

add_executable(NoLibC_Test
        test/main.c
)

target_link_libraries(NoLibC_Test NoLibC)