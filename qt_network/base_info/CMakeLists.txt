set(GET_BASE_INFO
    bi_main.cpp
    base_info.cpp
    base_info.h
)

qt5_wrap_cpp(GET_BASE_INFO_MOC_FILES ${GET_BASE_INFO})

add_executable(get_base_info 
                            ${GET_BASE_INFO}
                            ${GET_BASE_INFO_MOC_FILES}
)

target_link_libraries(get_base_info 
                                    Qt5::Core 
                                    Qt5::Gui 
                                    Qt5::Widgets 
                                    Qt5::Network
)
#================================================================================

