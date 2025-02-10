set(SHARE_PHOTO
    share_photo.cpp
)

qt5_wrap_cpp(SHARE_PHOTO_MOC_FILES ${SHARE_PHOTO})

add_executable(share_photo 
                            ${SHARE_PHOTO}
                            ${SHARE_PHOTO_MOC_FILES}
)

target_link_libraries(share_photo 
                                    Qt5::Core 
                                    Qt5::Gui 
                                    Qt5::Widgets
)

