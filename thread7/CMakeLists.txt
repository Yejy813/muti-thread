aux_source_directory(. SRC_FILES)

add_executable(thread7 ${SRC_FILES})

target_link_libraries(thread7 
                      pthread
                      )

target_install(thread7)
