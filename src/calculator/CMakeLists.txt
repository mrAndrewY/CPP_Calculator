cmake_minimum_required(VERSION 3.5)

project(s21_calc_c_plus_plus VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#if(APPLE AND NOT UNIX)
    find_package(QT NAMES Qt6  REQUIRED COMPONENTS Widgets LinguistTools)
#endif()
#if(UNIX AND NOT APPLE)
 #   find_package(QT NAMES Qt5 REQUIRED COMPONENTS Widgets LinguistTools) #Freebsd
#endif()
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

#if(APPLE)
find_package(Qt6PrintSupport REQUIRED)
find_package(Qt6 COMPONENTS Widgets PrintSupport REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS PrintSupport)
#endif()

if(UNIX AND NOT APPLE)
find_package(Qt5PrintSupport REQUIRED)
find_package(Qt5 COMPONENTS Widgets PrintSupport REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS PrintSupport)
endif()

set(TS_FILES calculator_en_001.ts)
set(PROJECT_SOURCES
        main.cc
        view.cc
        view.h
        view.ui
        graphic.cc
        graphic.h
        graphic.ui
        deposit_form.h
         credit_form.h
         deposit_form.cc
        credit_form.cc
        credit_form.ui
        deposit_form.ui
        qcustomplot.cc
        qcustomplot.h
        ../credit_persents_Model.cc
        ../Controller.h
        ../Controller.cc
	../Model.h
	../calc_Model.cc


)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(s21_calc_c_plus_plus
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET s21_calc_c_plus_plus APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(s21_calc_c_plus_plus SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(s21_calc_c_plus_plus
            ${PROJECT_SOURCES}
        )
    endif()
endif()

if(UNIX AND NOT APPLE)
    target_link_libraries(s21_calc_c_plus_plus PRIVATE Qt5::PrintSupport Qt${QT_VERSION_MAJOR}::Widgets) # freebsd
endif()
#if (APPLE AND NOT UNIX)
    target_link_libraries(s21_calc_c_plus_plus PRIVATE Qt6::PrintSupport Qt${QT_VERSION_MAJOR}::Widgets)
#endif()

set_target_properties(s21_calc_c_plus_plus PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

#install(TARGETS s21_calc_c_plus_plus
#    BUNDLE DESTINATION .
#    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(s21_calc_c_plus_plus)
endif()
