function(set_test name)
	project(${name}_test)
	
	# include gtest
	include(GoogleTest)
	
	# list sources
	file(GLOB_RECURSE sources *.h *.cpp)
	
	# create executable
	add_executable(${name}_test ${sources})
	
	# link gtest
	target_link_libraries(${name} PRIVATE GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)
	 
	# add to test list
	add_test(${name} ${name}_test)
endfunction()