cmake_minimum_required(VERSION 3.5)

project(serveurLivraison_libColisStatique VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories("/home/dnalexen/Documents/AJC_THALES/cours/11-PROJET C++/livraisonColis/ColisStatique")
link_directories("/home/dnalexen/Documents/AJC_THALES/cours/11-PROJET C++/livraisonColis/build-ColisStatique-Desktop_Qt_6_4_1_GCC_64bit-Debug")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Network)
find_package(Qt6 REQUIRED COMPONENTS Sql)

set(PROJECT_SOURCES
        main.cpp
        widget.cpp
        widget.h
        widget.ui
        camion.h
        camion.cpp
        dbmanager.h
        dbmanager.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(serveurLivraison_libColisStatique
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET serveurLivraison_libColisStatique APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(serveurLivraison_libColisStatique SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(serveurLivraison_libColisStatique
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(serveurLivraison_libColisStatique PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(serveurLivraison_libColisStatique PRIVATE "libColisStatique.a")
target_link_libraries(serveurLivraison_libColisStatique PRIVATE Qt${QT_VERSION_MAJOR}::Network)
target_link_libraries(serveurLivraison_libColisStatique PRIVATE Qt6::Sql)

set_target_properties(serveurLivraison_libColisStatique PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS serveurLivraison_libColisStatique
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(serveurLivraison_libColisStatique)
endif()
