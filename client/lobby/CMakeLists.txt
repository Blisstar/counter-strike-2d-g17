cmake_minimum_required(VERSION 3.16)

project(lobby VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

file(GLOB COMMON_SOURCES ../../common/*.cpp)

set(SOURCES
        ${COMMON_SOURCES}
        ../client_protocol.cpp
        main.cpp
        mainwindow.cpp
        mainmenuwindow.cpp
        premenu.cpp
        newgamewindow.cpp
        joingamewindow.cpp
        waitingguestwindow.cpp
        waitinghostwindow.cpp
)

set(UIS
        mainmenuwindow.ui
        premenu.ui
        newgamewindow.ui
        joingamewindow.ui
        waitingguestwindow.ui
        waitinghostwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(lobby
            MANUAL_FINALIZATION
            ${SOURCES}
            ${UIS}
    )
else()
    add_executable(lobby
            ${SOURCES}
            ${UIS}
    )
endif()

target_link_libraries(lobby PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(lobby)
endif()
