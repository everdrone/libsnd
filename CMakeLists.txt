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
