cmake_minimum_required(VERSION 3.5)

project(TexT_Editor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(TexT_Editor
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        Resources.qrc
        CustomDialog.h
        CustomDialog.cpp

        data/Dialogue/fielddata.h
        data/Dialogue/fielddata.cpp

        widgets/editor/EditorTools/editortools.h widgets/editor/EditorTools/editortools.cpp widgets/editor/EditorTools/editortools.ui
        widgets/editor/MainEditor/maineditor.h widgets/editor/MainEditor/maineditor.cpp widgets/editor/MainEditor/maineditor.ui
        widgets/editor/Designer/designer.h widgets/editor/Designer/designer.cpp widgets/editor/Designer/designer.ui
        widgets/editor/Fields/TextField/textfield.h widgets/editor/Fields/TextField/textfield.cpp widgets/editor/Fields/TextField/textfield.ui
        data/Dialogue/listdata.h data/Dialogue/listdata.cpp
        data/Dialogue/inputdata.h data/Dialogue/inputdata.cpp
        data/Dialogue/characterdata.h data/Dialogue/characterdata.cpp





    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET TexT_Editor APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(TexT_Editor SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(TexT_Editor
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(TexT_Editor PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.TexT_Editor)
endif()
set_target_properties(TexT_Editor PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS TexT_Editor
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(TexT_Editor)
endif()
