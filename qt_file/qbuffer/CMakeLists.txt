set(SIMPLE_QBUFFER
    simple_qbuffer.cpp
)

qt5_wrap_cpp(SIMPLE_QBUFFER_MOC_FILES ${SIMPLE_QBUFFER})

add_executable(simple_qbuffer 
                            ${SIMPLE_QBUFFER}
                            ${SIMPLE_QBUFFER_MOC_FILES}
)

target_link_libraries(simple_qbuffer 
                                    Qt5::Core 
                                    Qt5::Gui 
                                    Qt5::Widgets
)

