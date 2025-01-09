set(SIMPLE_TABLE_MODEL
    main.cpp
    connection.h
    tablemodelwidget.cpp
    tablemodelwidget.h
)

add_executable(simple_table_model 
                            ${SIMPLE_TABLE_MODEL}
)

target_link_libraries(simple_table_model 
                                    Qt5::Core 
                                    Qt5::Gui 
                                    Qt5::Widgets 
                                    Qt5::Sql
)

