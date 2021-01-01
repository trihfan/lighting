project(src)

# make lib
file(GLOB_RECURSE sources *.h *.cpp)
set_folder_structure("${sources}" ${src_path})
add_library(src STATIC ${sources})

# includes
target_include_directories(src PUBLIC ${src_path})

# set output directories
set_target_properties(src PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${lib_output_directory})
set_target_properties(src PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${lib_output_directory})
set_target_properties(src PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${bin_output_directory})
