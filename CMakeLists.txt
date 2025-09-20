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
        nolibc/private/syscall.h
        nolibc/intrinsic.c
        nolibc/write_buffer.c
        nolibc/private/write_buffer.h
        nolibc/public/nlc_types.h
        nolibc/memory.c
        nolibc/private/entry.h
        nolibc/entry.c
        nolibc/arena.c
        nolibc/file.c
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

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    # RelWithDebInfo: optimize, keep debug symbols, remove unused code
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -flto -ffunction-sections -fdata-sections -g -DNDEBUG")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -flto -Wl")
else()
    # Release or any other build: max optimization, remove debug info and unused code
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -flto -ffunction-sections -fdata-sections -DNDEBUG")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -flto -Wl")
endif()

if(APPLE)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-u,_memset")
else()
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-u,memset,--gc-sections -Wl")
endif()

target_link_libraries(NoLibC_Test NoLibC)