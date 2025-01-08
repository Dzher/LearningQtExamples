set(SIMPLE_QUERY_MODEL
    main.cpp
    connection.h
    querymodelwidget.cpp
    querymodelwidget.h
    myquerymodel.cpp
    myquerymodel.h
)

add_executable(simple_query_model 
                            ${SIMPLE_QUERY_MODEL}
)

target_link_libraries(simple_query_model 
                                    Qt5::Core 
                                    Qt5::Gui 
                                    Qt5::Widgets 
                                    Qt5::Sql
)

