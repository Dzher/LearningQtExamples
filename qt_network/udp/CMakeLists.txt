set(BROADCAST
    bc_main.cpp
    broadcast_sender.cpp
    broadcast_sender.h
    broadcast_receiver.cpp
    broadcast_receiver.h
)

qt5_wrap_cpp(BROADCAST_MOC_FILES ${BROADCAST})

add_executable(broadcast_by_udp 
                            ${BROADCAST}
                            ${BROADCAST_MOC_FILES}
)

target_link_libraries(broadcast_by_udp 
                                    Qt5::Core 
                                    Qt5::Gui 
                                    Qt5::Widgets 
                                    Qt5::Network
)
#================================================================================

