set(SIMPLE_WEB_BROWSER
    swb_main.cpp
    simple_web_browser.cpp
    simple_web_browser.h
)

qt5_wrap_cpp(SIMPLE_WEB_BROWSER_MOC_FILES ${SIMPLE_WEB_BROWSER})

add_executable(simple_web_browser 
                                ${SIMPLE_WEB_BROWSER}
                                ${SIMPLE_WEB_BROWSER_MOC_FILES}
)

target_link_libraries(simple_web_browser 
                                        Qt5::Core 
                                        Qt5::Gui 
                                        Qt5::Widgets 
                                        Qt5::Network
)
#================================================================================
set(SIMPLE_DOWNLOADER
    sd_main.cpp
    simple_downloader.cpp
    simple_downloader.h
)

qt5_wrap_cpp(SIMPLE_DOWNLOADER_MOC_FILES ${SIMPLE_DOWNLOADER})

add_executable(simple_downloader 
                                ${SIMPLE_DOWNLOADER}
                                ${SIMPLE_DOWNLOADER_MOC_FILES}
)

target_link_libraries(simple_downloader 
                                        Qt5::Core 
                                        Qt5::Gui 
                                        Qt5::Widgets 
                                        Qt5::Network
)
#================================================================================
