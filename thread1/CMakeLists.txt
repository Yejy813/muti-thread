aux_source_directory(. SRC_FILES)

add_executable(thread1 ${SRC_FILES})

target_link_libraries(thread1 
                      pthread
                      )

target_install(thread1)
