cmake_minimum_required(VERSION 3.12)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(version "1.0.0")
project(lighting VERSION ${version} LANGUAGES CXX)

# use c++17
set(CMAKE_CXX_STANDARD 17)

# modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
include(folder_structure)
include(set_test)

# directories
set(src_path ${PROJECT_SOURCE_DIR}/src)
set(test_path ${PROJECT_SOURCE_DIR}/tests)

# define output directories
set(lib_output_directory ${PROJECT_BINARY_DIR}/lib)
set(bin_output_directory ${PROJECT_BINARY_DIR}/bin)

# subdirectories
add_subdirectory(src)
add_subdirectory(tests)

# setup coral project directory
set_target_properties(src PROPERTIES FOLDER "lighting/src")