aux_source_directory(. SRC_FILES)

add_executable(thread8 ${SRC_FILES})

target_link_libraries(thread8 
                      pthread
                      )

target_install(thread8)
