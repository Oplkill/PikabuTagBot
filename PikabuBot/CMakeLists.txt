cmake_minimum_required(VERSION 3.5)

project(PikabuBot VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets LinguistTools Network WebEngineWidgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets LinguistTools Network WebEngineWidgets REQUIRED)

set(TS_FILES PikabuBot_ru_RU.ts)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.h
        mainwindow.cpp
        mainwindow.ui
        networkpagepostsparser.h
        networkpagepostsparser.cpp
        editingdata.h
        editingdata.cpp
        networksearchposts.h 
        networksearchposts.cpp
        collectingpostsdialog.h 
        collectingpostsdialog.cpp
        collectingpostsdialog.ui
        tagmanager.h 
        tagmanager.cpp
        browser/browser.h
        browser/browser.cpp
        browser/browserwindow.h
        browser/browserwindow.cpp
        browser/tabwidget.h
        browser/tabwidget.cpp
        browser/webpage.h
        browser/webpage.cpp
        browser/webpopupwindow.h
        browser/webpopupwindow.cpp
        browser/webview.h
        browser/webview.cpp
        browser/passworddialog.ui
        browser/certificateerrordialog.ui
        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(PikabuBot
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET PikabuBot APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(PikabuBot SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(PikabuBot
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(PikabuBot PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network Qt${QT_VERSION_MAJOR}::WebEngineWidgets)

set_target_properties(PikabuBot PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(PikabuBot)
endif()
