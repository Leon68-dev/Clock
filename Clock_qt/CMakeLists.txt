cmake_minimum_required(VERSION 3.16)
project(Clock_qt VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Network Multimedia)

set(SOURCES
    main.cpp
    src/MainWindow.h
    src/MainWindow.cpp
    src/SetupDialog.h   
    src/SetupDialog.cpp 
    src/SystemMonitor.h
    src/SystemMonitor.cpp
    res/resources.qrc
)

add_executable(Clock_qt WIN32 ${SOURCES})

target_include_directories(Clock_qt PRIVATE src)

target_link_libraries(Clock_qt PRIVATE 
    Qt6::Widgets 
    Qt6::Network 
    Qt6::Multimedia
)