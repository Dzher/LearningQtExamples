set(SIMPLE_DEMO
    main.cpp
)

add_executable(simple_db_demo 
                            ${SIMPLE_DEMO}
)

target_link_libraries(simple_db_demo 
                                    Qt5::Core 
                                    Qt5::Sql
)

