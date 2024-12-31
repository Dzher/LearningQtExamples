set(CONNECT
    cnc_main.cpp
    connect_client.cpp
    connect_client.h
    connect_server.cpp
    connect_server.h
)

qt5_wrap_cpp(CONNECT_MOC_FILES ${CONNECT})

add_executable(connect_by_tcp 
                            ${CONNECT}
                            ${CONNECT_MOC_FILES}
)

target_link_libraries(connect_by_tcp 
                                    Qt5::Core 
                                    Qt5::Gui 
                                    Qt5::Widgets 
                                    Qt5::Network
)
#================================================================================

