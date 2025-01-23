set(GET_FILE_INFO
    info_main.cpp
)

qt5_wrap_cpp(GET_INFO_MOC_FILES ${GET_FILE_INFO})

add_executable(get_file_info 
                            ${GET_FILE_INFO}
                            ${GET_INFO_MOC_FILES}
)

target_link_libraries(get_file_info 
                                    Qt5::Core 
                                    Qt5::Gui 
                                    Qt5::Widgets
)

