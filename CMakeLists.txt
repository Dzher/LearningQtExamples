cmake_minimum_required(VERSION 3.21)
project(LearningQtExamples)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Qt5 COMPONENTS 
                            Core
                            Gui 
                            Widgets 
                            Network 
                            Sql 
                            REQUIRED)

# sub directories
add_subdirectory(qt_network)
add_subdirectory(qt_database)
add_subdirectory(qt_file)
add_subdirectory(qt_process)


