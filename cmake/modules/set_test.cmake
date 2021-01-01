function(set_test name)
	project(${name}_test)
	
	# include gtest
	include(GoogleTest)
	
	# list sources
	file(GLOB_RECURSE sources *.h *.cpp)
	
	# includes
	include_directories(${name}_test ${src_path})

	# create executable
	add_executable(${name}_test ${sources})
	set_target_properties(${name}_test PROPERTIES FOLDER "lighting/tests/${name}")

	# link
	target_link_libraries(${name}_test PRIVATE GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main src)
	 
	# add to test list
	add_test(${name} ${name}_test)
endfunction()