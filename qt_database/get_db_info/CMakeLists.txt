set(GET_INFO
    info_main.cpp
)

qt5_wrap_cpp(GET_INFO_MOC_FILES ${GET_INFO})

add_executable(get_db_info 
                            ${GET_INFO}
                            ${GET_INFO_MOC_FILES}
)

target_link_libraries(get_db_info 
                                    Qt5::Core 
                                    Qt5::Gui 
                                    Qt5::Widgets
                                    Qt5::Sql
)
#================================================================================

