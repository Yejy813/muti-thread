aux_source_directory(. SRC_FILES)

add_executable(thread5 ${SRC_FILES})

target_link_libraries(thread5 
                      pthread
                      )

target_install(thread5)
