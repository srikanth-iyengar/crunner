cmake_minimum_required(VERSION 3.28)

project(c-runner VERSION 1.0 LANGUAGES C)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -flto")

set(PARSER_DIR "${CMAKE_CURRENT_BINARY_DIR}")
set(SRC_DIR "src")
set(INCLUDE_DIR "include")
set(LIBEVENT_STATIC_LINK TRUE)

find_package(Curses REQUIRED)
find_package(FLEX 2.6 REQUIRED)
find_package(BISON 3.0 REQUIRED)
find_package(LibEvent REQUIRED)

set(LEXER_OUT "${PARSER_DIR}/lex.yy.c")
set(PARSER_OUT "${PARSER_DIR}/rn.tab.c")

include_directories(${CURSES_INCLUDE_DIR})
include_directories("${SRC_DIR}")

flex_target(LEXER "${SRC_DIR}/lib/token.l" "${LEXER_OUT}" DEFINES_FILE "${PARSER_DIR}/lex.yy.h")
bison_target(PARSER "${SRC_DIR}/lib/rn.y" "${PARSER_OUT}" DEFINES_FILE "${PARSER_DIR}/rn.tab.h")

add_flex_bison_dependency(LEXER PARSER)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.c")

add_executable(main "${LEXER_OUT}" "${PARSER_OUT}" ${SOURCES})

target_include_directories(main PUBLIC "${PARSER_DIR}" "${INCLUDE_DIR}")
target_link_libraries(main PUBLIC ${CURSES_LIBRARIES})
