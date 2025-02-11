set(LED_DEMO
    led_demo.h
)

qt5_wrap_cpp(LED_DEMO_MOC_FILES ${LED_DEMO})

add_executable(led_demo 
                            ${LED_DEMO}
                            ${LED_DEMO_MOC_FILES}
)

target_link_libraries(led_demo 
                                    Qt5::Core 
                                    Qt5::Gui 
                                    Qt5::Widgets
)
#================================================================================
set(STOP_WATCH
    stop_watch.h
)

qt5_wrap_cpp(STOP_WATCH_MOC_FILES ${STOP_WATCH})

add_executable(stop_watch 
                            ${STOP_WATCH}
                            ${STOP_WATCH_MOC_FILES}
)

target_link_libraries(stop_watch 
                                    Qt5::Core 
                                    Qt5::Gui 
                                    Qt5::Widgets
)

