cmake_minimum_required(VERSION 3.10)

# set the project name
set(PROGRAMNAME "lilacs")
project(${PROGRAMNAME})


# add the executable
add_executable(${PROGRAMNAME} main.c)
add_library(flags flags.c)
target_link_libraries(${PROGRAMNAME} hello)

