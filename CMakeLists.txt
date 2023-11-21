cmake_minimum_required(VERSION 3.16)

project(FileDialog LANGUAGES CXX VERSION 3.0.0)

set(COMPANY "Radar-MMS")
set(COPYRIGHT "Copyright (c) 2023 ${COMPANY}. All rights reserved.")
set(IDENTIFIER "${PROJECT_NAME}")

if(TARGET ${PROJECT_NAME})
    return()
endif()

if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 20)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif(NOT CMAKE_CXX_STANDARD)

set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

find_package(QT NAMES Qt5 REQUIRED COMPONENTS Core Quick)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS
    Core
    Quick
    QuickControls2
    Widgets
)

add_library(${PROJECT_NAME} ${CPP_SOURCES} ${QRC_SOURCES})


target_sources(${PROJECT_NAME}
    PUBLIC
    include/FileDialog/Register

    PRIVATE
    src/c++/filesmanager.cpp          src/c++/filesmanager.h
    src/c++/register.cpp              src/c++/register.h
    src/c++/sortedmodel.cpp           src/c++/sortedmodel.h
    src/c++/utils/filesutils.cpp            src/c++/utils/filesutils.h
    src/c++/types/filenode.h
    src/qml/fileDialogQml.qrc
    resources/fileDialogRc.qrc
 )
target_include_directories(${PROJECT_NAME}
    PUBLIC
    include/

    PRIVATE
    src/c++/
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Quick
    Qt${QT_VERSION_MAJOR}::QuickControls2
    Qt${QT_VERSION_MAJOR}::Widgets
)

add_subdirectory(libs)



execute_process(COMMAND git describe --tags --always WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} OUTPUT_VARIABLE GIT_VERSION OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND ${CMAKE_COMMAND} -E env TZ=UTC git log -1 --format=%cd --date=format-local:"%d.%m.%Y %H:%M:%S" WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} OUTPUT_VARIABLE GIT_SOURCE_DATE OUTPUT_STRIP_TRAILING_WHITESPACE)
string(TIMESTAMP PROJECT_BUILD_DATE "%d.%m.%Y %H:%M:%S" UTC)
add_definitions(
    -DPROJECT_NAME="${PROJECT_NAME}"
    -DPROJECT_COMPANY="${COMPANY}"
    -DPROJECT_VERSION="${GIT_VERSION}"
    -DPROJECT_SOURCE_DATE=${GIT_SOURCE_DATE}
    -DPROJECT_BUILD_DATE="${PROJECT_BUILD_DATE}"
)
