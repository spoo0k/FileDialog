cmake_minimum_required(VERSION 3.16)

project(FileDialog LANGUAGES CXX VERSION 3.0.0)

set(COMPANY "Radar-MMS")
set(COPYRIGHT "Copyright (c) 2023 ${COMPANY}. All rights reserved.")
set(IDENTIFIER "${PROJECT_NAME}")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt5 REQUIRED COMPONENTS Core Quick)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS
    Core
    Quick
    QuickControls2
    Concurrent
    Widgets
    Positioning
    Location
    Network
)

include_directories(src/c++ libs)

file(GLOB_RECURSE CPP_SOURCES
    src/c++/*
)

set(PROJECT_EXAMPLES
    examples/main.cpp
    examples/example.qrc
)

set(PROJECT_SOURCES
    src/qml/qml.qrc
    resources/resources.qrc
)

add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCES}
    ${CPP_SOURCES}
    ${PROJECT_EXAMPLES}
)

add_subdirectory(libs)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Quick
    Qt${QT_VERSION_MAJOR}::QuickControls2
    Qt${QT_VERSION_MAJOR}::Widgets
)

add_definitions(
    -DPROJECT_NAME="${PROJECT_NAME}"
    -DPROJECT_VERSION="${PROJECT_VERSION}"
    -DPROJECT_COMPANY="${COMPANY}"
)

message("${PROJECT_NAME} version ${PROJECT_VERSION} compiled successfully")
