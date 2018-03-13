cmake_minimum_required( VERSION 3.2.2 )
project( libsnd VERSION 0.0.8 )

### Standard
set( CMAKE_CXX_STANDARD 14 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )

### Verbosity
set( CMAKE_COLOR_MAKEFILE ON )
set( CMAKE_VERBOSE_MAKEFILE ON )

option(BUILD_TESTS "Build unit tests" ON)

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
	source/conversion.cc
	source/denormal.cc
	source/envelope.cc
	source/interpolation.cc
	source/lfo.cc
	source/sine.cc
)

target_include_directories(
	libsnd
	PRIVATE
	include
)

set_target_properties(
	libsnd PROPERTIES
	VERSION ${libsnd_VERSION}
	PREFIX ""
	DEBUG_POSTFIX "d"
)

### Tests

if (BUILD_TESTS)
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
endif()

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

install(
	TARGETS libsnd 
	EXPORT libsnd-targets 
	ARCHIVE DESTINATION lib
)

install(
	FILES ${CMAKE_SOURCE_DIR}/include/snd.h
	DESTINATION include
)

set(CONF_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/lib/cmake/${CMAKE_PROJECT_NAME}")

write_basic_package_version_file(
	"${CMAKE_BINARY_DIR}/libsnd-config-version.cmake"
	COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
	"${CMAKE_SOURCE_DIR}/libsnd-config.cmake.in"
	"${CMAKE_BINARY_DIR}/libsnd-config.cmake"
	INSTALL_DESTINATION ${CONF_INSTALL_DIR}
	PATH_VARS CMAKE_INSTALL_FULL_INCLUDEDIR CMAKE_INSTALL_FULL_LIBDIR
)

install(
	EXPORT libsnd-targets
	FILE libsnd-targets.cmake
	DESTINATION ${CONF_INSTALL_DIR}
)

install(
	FILES ${CMAKE_BINARY_DIR}/libsnd-config.cmake ${CMAKE_BINARY_DIR}/libsnd-config-version.cmake
	DESTINATION ${CONF_INSTALL_DIR}
)
