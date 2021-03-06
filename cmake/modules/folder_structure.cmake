function(set_folder_structure sources path)
	foreach(source IN ITEMS ${sources})
		get_filename_component(sources_path "${source}" PATH)
		file(RELATIVE_PATH sources_path_rel "${path}" "${sources_path}")
		string(REPLACE "/" "\\" group_path "${sources_path_rel}")
		source_group("${group_path}" FILES "${source}")
	endforeach()
endfunction()