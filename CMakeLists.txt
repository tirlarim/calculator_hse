cmake_minimum_required(VERSION 3.22 FATAL_ERROR)
project(calculator_hse_lib VERSION 1.0.3 LANGUAGES C)

# Configure Flags
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(ERROR_FLAGS "-Werror -Wall -Werror=vla -Wno-deprecated-declarations")
set(OPTIMIZATION_FLAGS "-march=native")
if(CMAKE_BUILD_TYPE STREQUAL "Release")
  set(RELEASE_FLAGS "-Ofast")
  set(RELEASE_CHECKS "-Wextra -pedantic -Wno-unused-parameter")
  string(APPEND CMAKE_C_FLAGS " ${ERROR_FLAGS} ${OPTIMIZATION_FLAGS} ${RELEASE_FLAGS} ${RELEASE_CHECKS}")
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(DEBUG_REMOVED_CHECKS "-Wno-unused-function -Wno-unused-but-set-variable -Wno-unused-variable -Wno-unused-parameter -Wno-unused-private-field")
  string(APPEND CMAKE_C_FLAGS " ${ERROR_FLAGS} ${OPTIMIZATION_FLAGS} ${DEBUG_REMOVED_CHECKS}")
endif()
add_compile_options(-Wunused-variable)
add_compile_options(-Wno-error=unused-variable)
add_compile_options(-Wunused-local-typedef)
add_compile_options(-Wno-error=unused-local-typedef)

file(GLOB_RECURSE SRC "src/*.c")
file(GLOB_RECURSE HEADERS "src/*.h")

#Configure Lib
add_library(${PROJECT_NAME} STATIC ${SRC} ${HEADERS})
target_include_directories(${PROJECT_NAME} PRIVATE ${HEADERS})
