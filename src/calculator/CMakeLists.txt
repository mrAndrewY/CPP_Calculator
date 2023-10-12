cmake_minimum_required(VERSION 3.5)

project(s21_calc_c_plus_plus VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Qt6PrintSupport REQUIRED)
find_package(Qt6 COMPONENTS Widgets PrintSupport REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS PrintSupport)

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

    qt_add_executable(s21_calc_c_plus_plus
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )

    target_link_libraries(s21_calc_c_plus_plus PRIVATE Qt6::PrintSupport Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(s21_calc_c_plus_plus PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)


if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(s21_calc_c_plus_plus)
endif()
