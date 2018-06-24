cmake_minimum_required( VERSION 3.2.2 )
project( libsnd VERSION 0.0.8 )

### Standard
set( CMAKE_CXX_STANDARD 14 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )

### Verbosity
set( CMAKE_COLOR_MAKEFILE ON )
set( CMAKE_VERBOSE_MAKEFILE ON )

option( BUILD_TESTS "Build unit tests" ON )

### Targets

add_library(
	libsnd
	STATIC
	source/approx.cpp
	source/conversion.cpp
	source/denormal.cpp
	source/envelope.cpp
	source/interpolation.cpp
	source/lfo.cpp
	source/sawtooth.cpp
	source/sine.cpp
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

### dist
set( ARCHIVE_NAME ${CMAKE_PROJECT_NAME}-${libsnd_VERSION} )
add_custom_target(dist
		COMMAND tar -czf "${CMAKE_PROJECT_NAME}-${libsnd_VERSION}.tar.gz" source/
			include/
			docs/
			examples/
			test/
			.gitignore
			CHANGELOG.md
			CMakeLists.txt
			Doxyfile
			libsnd-config.cmake.in
			LICENSE
			README.md
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})


### Optimizations
if ( MSVC )
	target_compile_options(
		libsnd
		PUBLIC
		/W4
	)
elseif( CMAKE_COMPILER_IS_GNUCXX )
	target_compile_options(
		libsnd
		PUBLIC
		-O2
		-Wall
		-Wextra
	)
endif()

### Tests
if ( BUILD_TESTS )
	enable_testing()

	add_executable(
		Test
		test/test.cpp
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

include( CMakePackageConfigHelpers )
include( GNUInstallDirs )

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
