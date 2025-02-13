set(EVENT_STEP
    event_step.cpp
)

# qt5_wrap_cpp(EVENT_STEP_MOC_FILES ${EVENT_STEP})

add_executable(event_step 
                            ${EVENT_STEP}
                            # ${EVENT_STEP_MOC_FILES}
)

target_link_libraries(event_step 
                                    Qt5::Core 
                                    Qt5::Gui 
                                    Qt5::Widgets
)

