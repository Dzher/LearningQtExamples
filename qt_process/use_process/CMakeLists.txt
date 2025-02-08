set(SIMPLE_PROCESS
    simple_process.cpp
)

qt5_wrap_cpp(SIMPLE_PROCESS_MOC_FILES ${SIMPLE_PROCESS})

add_executable(simple_process 
                            ${SIMPLE_PROCESS}
                            ${SIMPLE_PROCESS_MOC_FILES}
)

target_link_libraries(simple_process 
                                    Qt5::Core 
                                    Qt5::Gui 
                                    Qt5::Widgets
)

