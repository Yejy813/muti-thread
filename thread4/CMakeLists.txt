aux_source_directory(. SRC_FILES)

add_executable(thread4 ${SRC_FILES})

target_link_libraries(thread4 
                      pthread
                      )

target_install(thread4)
