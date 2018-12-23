aux_source_directory(. SRC_FILES)

add_executable(thread3 ${SRC_FILES})

target_link_libraries(thread3 
                      pthread
                      )

target_install(thread3)
