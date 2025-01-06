set(SIMPLE_QUERY
    main.cpp
    connection.h
    query_widget.cpp
    query_widget.h
)

add_executable(simple_query 
                            ${SIMPLE_QUERY}
)

target_link_libraries(simple_query 
                                    Qt5::Core 
                                    Qt5::Gui 
                                    Qt5::Widgets 
                                    Qt5::Sql
)

