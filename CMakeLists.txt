cmake_minimum_required(VERSION 3.22 FATAL_ERROR)
project(calculator_hse VERSION 1.0.3 LANGUAGES C)

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

# SET SRC
file(GLOB_RECURSE SRC "src/*.c")
file(GLOB_RECURSE HEADERS "src/*.h")

# Configure GTK3
find_package(PkgConfig 0.29.0 REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
add_definitions(${GTK3_CFLAGS_OTHER})
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

add_executable(${PROJECT_NAME} ${SRC} ${HEADERS})

set(GUI_GLADE_SOURCE ${CMAKE_SOURCE_DIR}/view/gui.glade)
set(ICON_PNG_SOURCE ${CMAKE_SOURCE_DIR}/view/icon.png)
set(GUI_GLADE_DESTINATION ${CMAKE_BINARY_DIR}/view/gui.glade)
set(ICON_PNG_DESTINATION ${CMAKE_BINARY_DIR}/view/icon.png)
configure_file(${GUI_GLADE_SOURCE} ${GUI_GLADE_DESTINATION} COPYONLY)
configure_file(${ICON_PNG_SOURCE} ${ICON_PNG_DESTINATION} COPYONLY)

# Configure Target
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${HEADERS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${GTK3_LIBRARIES})
