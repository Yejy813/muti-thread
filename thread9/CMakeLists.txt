aux_source_directory(. SRC_FILES)

add_executable(thread9 ${SRC_FILES})

target_link_libraries(thread9 
                      pthread
                      )

target_install(thread9)
