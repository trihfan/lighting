project(tests)

# enable testing
enable_testing()
find_package(GTest CONFIG REQUIRED)

# tests
add_subdirectory(tuple)
add_subdirectory(canvas)
add_subdirectory(matrix)
add_subdirectory(ray)