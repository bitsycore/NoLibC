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
        nolibc/system.c
        nolibc/print.c
        nolibc/private/system.h
        nolibc/intrinsic.c
        nolibc/write_buffer.c
        nolibc/private/write_buffer.h
        nolibc/public/nlc_types.h
        nolibc/memory.c
        nolibc/private/entry.h
        nolibc/entry.c
        nolibc/arena.c
        nolibc/file.c
        nolibc/public/nlc_arena.h
        nolibc/public/nlc_memory.h
        nolibc/private/intrinsic.h
        nolibc/public/nlc_file.h
        nolibc/public/nlc_system.h
        nolibc/public/nlc_string.h
        nolibc/public/nlc_print.h
        nolibc/format.c
        nolibc/public/nlc_format.h
)

target_compile_options(NoLibC PUBLIC ${COMMON_COMPILE_OPTIONS})
target_link_options(NoLibC PUBLIC ${COMMON_LINK_OPTIONS})

# ===================================================================================
# MARK: NOLIBC_Test
# ===================================================================================

add_executable(NoLibC_Test
        test/main.c
)

target_include_directories(
        NoLibC_Test PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/nolibc/public
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    # RelWithDebInfo: optimize, keep debug symbols, remove unused code
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -flto -ffunction-sections -fdata-sections -g -DNDEBUG")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -flto")
else()
    # Release or any other build: max optimization, remove debug info and unused code
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -flto -ffunction-sections -fdata-sections -DNDEBUG")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -flto")
endif()

if(APPLE)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-u,_memset")
else()
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-u,memset,--gc-sections")
endif()

target_compile_options(NoLibC_Test PUBLIC ${COMMON_COMPILE_OPTIONS})
target_link_options(NoLibC_Test PUBLIC ${COMMON_LINK_OPTIONS})
target_link_libraries(NoLibC_Test NoLibC)