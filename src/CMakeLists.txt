cmake_minimum_required(VERSION 3.10)

# set the project name
set(PROGRAMNAME "lilacs")
project(${PROGRAMNAME})


# add the executable
add_library(flags flags.c)
add_executable(${PROGRAMNAME} main.c)
target_link_libraries(${PROGRAMNAME} hello)

