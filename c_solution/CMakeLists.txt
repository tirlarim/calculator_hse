cmake_minimum_required(VERSION 3.20)
project(c_solution C)

set(CMAKE_C_STANDARD 11)

add_executable(c_solution calculator_main.c arrays.c arrays.h arrays.c arrays.h polish.c polish.h is_smh_compare.c is_smh_compare.h actions.c actions.h calculations.c calculations.h variables.c variables.h operations_functions.c operations_functions.h)
