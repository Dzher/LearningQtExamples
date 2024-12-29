set(SIMPLY_WEB_BROWSER
    swb_main.cpp
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
#================================================================================
set(SIMPLY_DOWNLOADER
    sd_main.cpp
    simply_downloader.cpp
    simply_downloader.h
)

qt5_wrap_cpp(SIMPLY_DOWNLOADER_MOC_FILES ${SIMPLY_DOWNLOADER})

add_executable(simply_downloader 
                                ${SIMPLY_DOWNLOADER}
                                ${SIMPLY_DOWNLOADER_MOC_FILES}
)

target_link_libraries(simply_downloader 
                                        Qt5::Core 
                                        Qt5::Gui 
                                        Qt5::Widgets 
                                        Qt5::Network
)
#================================================================================
