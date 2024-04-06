cmake_minimum_required(VERSION 3.27.8 FATAL_ERROR)
project(c_solution)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(SOURCE_FILES gui gui.c arrays.c arrays.h polish.c polish.h is_smh_compare.c is_smh_compare.h actions.c actions.h calculations.c calculations.h variables.c variables.h operations_functions.c operations_functions.h)


find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
add_definitions(${GTK3_CFLAGS_OTHER})

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

add_executable(c_solution ${SOURCE_FILES})

target_link_libraries(c_solution ${GTK3_LIBRARIES})
