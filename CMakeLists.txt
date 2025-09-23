cmake_minimum_required(VERSION 3.20)
project(NoLibC C)
set(CMAKE_C_STANDARD 23)

# =======================
# MARK: COMMON OPTIONS
# =======================

set(COMMON_LINK_OPTIONS
		-fno-builtin
		-fno-stack-protector
		-nostdlib
		-nodefaultlibs
)

if (APPLE)
	list(APPEND COMMON_LINK_OPTIONS -Wl,-lSystem)
endif ()

set(COMMON_COMPILE_OPTIONS
		-fno-builtin
		-fno-stack-protector
		-nostdinc
)

# =======================
# MARK: COMPILER FLAGS
# =======================

# Common
set(FLAGS_COMP_COMMON "-flto -ffunction-sections -fdata-sections")

# BuildType
if (CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")

	# Optimize but keep debug info
	set(FLAGS_COMP_BUILD_TYPE "-O3 -g -DNDEBUG")

elseif (CMAKE_BUILD_TYPE STREQUAL "Release")

	# Full optimization, strip all symbols
	set(FLAGS_COMP_BUILD_TYPE "-Ofast -s -DNDEBUG")

elseif (CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")

	# Speed optimization, strip all symbols
	if (CMAKE_C_COMPILER_ID STREQUAL "Clang")
		set(FLAGS_COMP_BUILD_TYPE "-Oz -s -DNDEBUG")
		message("Using Clang -Oz")
	else ()
		set(FLAGS_COMP_BUILD_TYPE "-Os -s -DNDEBUG")
		message("Using GCC -Os")
	endif ()

else ()

	set(FLAGS_COMP_BUILD_TYPE "-O0 -g")

endif ()

# Apply compiler flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${FLAGS_COMP_BUILD_TYPE} ${FLAGS_COMP_COMMON}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLAGS_COMP_BUILD_TYPE} ${FLAGS_COMP_COMMON}")

# =======================
# MARK: LINKER FLAGS
# =======================

# Common
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -flto")

# Platform
if (APPLE)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-u,_memset")
else ()
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-u,memset,--gc-sections")
endif ()

# =======================
# MARK: NOLIBC
# =======================

add_library(NoLibC STATIC
		nolibc/arena.c
		nolibc/entry.c
		nolibc/file.c
		nolibc/format.c
		nolibc/intrinsic.c
		nolibc/memory.c
		nolibc/print.c
		nolibc/private/entry.h
		nolibc/private/intrinsic.h
		nolibc/private/system.h
		nolibc/private/filewritebuffer.h
		nolibc/public/nlc.h
		nolibc/public/nlc_arena.h
		nolibc/public/nlc_file.h
		nolibc/public/nlc_format.h
		nolibc/public/nlc_memory.h
		nolibc/public/nlc_print.h
		nolibc/public/nlc_string.h
		nolibc/public/nlc_system.h
		nolibc/public/nlc_terminal.h
		nolibc/public/nlc_types.h
		nolibc/string.c
		nolibc/system.c
		nolibc/filewritebuffer.c
		nolibc/public/nlc_varg.h
		nolibc/iwriter.c
		nolibc/public/nlc_iwriter.h
		nolibc/stringbuffer.c
		nolibc/public/nlc_stringbuffer.h
		nolibc/public/nlc_maths.h
)

target_compile_options(NoLibC PUBLIC ${COMMON_COMPILE_OPTIONS})
target_link_options(NoLibC PUBLIC ${COMMON_LINK_OPTIONS})

# =======================
# MARK: NOLIBC_Test
# =======================

add_executable(NoLibC_Test
		test.c
)

target_include_directories(NoLibC_Test PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/nolibc/public
)

target_compile_options(NoLibC_Test PRIVATE ${COMMON_COMPILE_OPTIONS})
target_link_options(NoLibC_Test PRIVATE ${COMMON_LINK_OPTIONS})
target_link_libraries(NoLibC_Test NoLibC)