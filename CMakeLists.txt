cmake_minimum_required( VERSION 3.2.2 )
project( libsnd )

### Standard
set( CMAKE_CXX_STANDARD 14 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )

### Verbosity
set( CMAKE_COLOR_MAKEFILE ON )
set( CMAKE_VERBOSE_MAKEFILE ON )

### Optimizations
if( MSVC )
	add_compile_options( /W4 )
elseif( CMAKE_COMPILER_IS_GNUCXX )
	add_compile_options( -O2 )
	add_compile_options( -Wall )
	add_compile_options( -Wextra )
endif()


### Targets

add_library(
	libsnd
	STATIC
	source/approx.cc
	source/denormal.cc
	source/envelope.cc
	source/interpolation.cc
	source/sine.cc
)

target_include_directories(
	libsnd
	PRIVATE
	include
)

set(LIBSND_VERSION_MAJOR 0)
set(LIBSND_VERSION_MINOR 0)
set(LIBSND_VERSION_PATCH 6)
set(LIBSND_VERSION_STRING "${LIBSND_VERSION_MAJOR}.${LIBSND_VERSION_MINOR}.${LIBSND_VERSION_PATCH}")

set_target_properties(
	libsnd PROPERTIES
	VERSION ${LIBSND_VERSION_STRING}
)

install(TARGETS libsnd DESTINATION lib)

install(FILES include/snd.h DESTINATION include)

### Tests
enable_testing()

add_executable(
	Test
	tests/test.cc
)

target_include_directories(
	Test
	PRIVATE
	include
)

target_link_libraries(
	Test
	PRIVATE
	libsnd
)

add_test(
	NAME Test
	COMMAND Test
)
