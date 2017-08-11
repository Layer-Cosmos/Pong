cmake_minimum_required(VERSION 2.6)
project(Pong)

set(FONT_NAME "font.ttf")
add_definitions(-DFONT_PATH="${CMAKE_CURRENT_SOURCE_DIR}/src/${FONT_NAME}")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wextra -g -O0 -lm")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

add_subdirectory(src)
