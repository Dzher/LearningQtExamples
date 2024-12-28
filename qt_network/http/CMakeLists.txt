set(SIMPLY_WEB_BROWSER
    main.cpp
    simply_web_browser.cpp
    simply_web_browser.h
)

qt5_wrap_cpp(SIMPLY_WEB_BROWSER_MOC_FILES ${SIMPLY_WEB_BROWSER})

add_executable(simply_web_browser 
                                ${SIMPLY_WEB_BROWSER}
                                ${SIMPLY_WEB_BROWSER_MOC_FILES}
)

target_link_libraries(simply_web_browser 
                                        Qt5::Core 
                                        Qt5::Gui 
                                        Qt5::Widgets 
                                        Qt5::Network
)
