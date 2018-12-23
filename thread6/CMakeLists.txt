aux_source_directory(. SRC_FILES)

add_executable(thread6 ${SRC_FILES})

target_link_libraries(thread6 
                      pthread
                      )

target_install(thread6)
