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

