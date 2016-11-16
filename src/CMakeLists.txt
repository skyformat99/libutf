cmake_minimum_required(VERSION 2.6)

include_directories("../include")

if (CMAKE_COMPILER_IS_GNUCC OR "${CMAKE_C_COMPILER}" STREQUAL "Clang")
	set (CMAKE_C_FLAGS "-Wall -Wextra -Werror -Wfatal-errors -ansi -pedantic")
elseif (MSVC)
	set (CMAKE_C_FLAGS "/Wall /WX /wd4710 /wd4711")
endif (CMAKE_COMPILER_IS_GNUCC OR "${CMAKE_C_COMPILER}" STREQUAL "Clang")

set (LIBUTF_HEADERS
	"converter.h"
	"decoder.h"
	"encoder.h"
	"error.h"
	"utf8.h"
	"utf16.h"
	"utf32.h"
	"version.h")

set (LIBUTF_SOURCES
	"converter.c"
	"decoder.c"
	"encoder.c"
	"error.c"
	"utf8.c"
	"utf16.c"
	"utf32.c")

add_library("utf-shared" SHARED ${LIBUTF_SOURCES})
set_target_properties("utf-shared" PROPERTIES OUTPUT_NAME "utf")

add_library("utf-static" STATIC ${LIBUTF_SOURCES})
set_target_properties("utf-static" PROPERTIES OUTPUT_NAME "utf")

if (WIN32 AND MSVC)
	set_target_properties("utf-shared" PROPERTIES
		SOVERSION ${LIBUTF_VERSION}
		LINK_FLAGS "/def:${PROJECT_SOURCE_DIR}/utf.def")
endif (WIN32 AND MSVC)

install(TARGETS
		"utf-static"
		"utf-shared"
	RUNTIME DESTINATION "bin"
	ARCHIVE DESTINATION "lib"
	LIBRARY DESTINATION "lib")

if (WIN32)
	install(FILES "libutf-config.cmake"
		DESTINATION "cmake")
elseif (UNIX)
	install(FILES "libutf-config.cmake"
		DESTINATION "share/libutf/cmake")
endif (WIN32)

install(FILES ${LIBUTF_HEADERS}
	DESTINATION "include/libutf")

enable_testing()

function(ADD_UTF_TEST TEST_NAME)
	add_executable(${TEST_NAME} ${ARGN})
	target_link_libraries(${TEST_NAME} "utf-static")
	if (MSVC)
		set_target_properties(${TEST_NAME} PROPERTIES COMPILE_FLAGS "/UNDEBUG")
	else (MSVC)
		set_target_properties(${TEST_NAME} PROPERTIES COMPILE_FLAGS "-UNDEBUG")
	endif (MSVC)
	add_test(${TEST_NAME} ${TEST_NAME})
endfunction(ADD_UTF_TEST TEST_NAME)

add_utf_test("utf8-test" "utf8-test.c")
add_utf_test("utf16-test" "utf16-test.c")
add_utf_test("decoder-test" "decoder-test.c")
add_utf_test("encoder-test" "encoder-test.c")
add_utf_test("converter-test" "converter-test.c")
