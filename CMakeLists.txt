cmake_minimum_required(VERSION 3.5)

project(TexT_Editor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS WebEngineWidgets)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(PROJECT_SOURCES
        main.cpp



)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(TexT_Editor
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        Resources.qrc
        CustomDialog.h
        CustomDialog.cpp

        data/Fields/fielddata.h
        data/Fields/fielddata.cpp
        data/Fields/MainFields/mainfielddata.h
        data/Fields/MainFields/mainfielddata.cpp
        data/Fields/MainFields/input/inputdata.h
        data/Fields/MainFields/input/inputdata.cpp
        data/Fields/MainFields/list/listdata.h
        data/Fields/MainFields/list/listdata.cpp
        data/Fields/MainFields/text/textdata.h
        data/Fields/MainFields/text/textdata.cpp
        data/Fields/SubFields/subfielddata.h
        data/Fields/SubFields/subfielddata.cpp
        data/Fields/SubFields/character/characterdata.h
        data/Fields/SubFields/character/characterdata.cpp

        data/ConnectionData/connectionData.h
        data/ConnectionData/connectionData.cpp

        widgets/editor/EditorTools/editortools.h widgets/editor/EditorTools/editortools.cpp widgets/editor/EditorTools/editortools.ui
        widgets/editor/MainEditor/maineditor.h widgets/editor/MainEditor/maineditor.cpp widgets/editor/MainEditor/maineditor.ui
        widgets/editor/Designer/designer.h widgets/editor/Designer/designer.cpp widgets/editor/Designer/designer.ui
        widgets/editor/Fields/TextField/textfield.h widgets/editor/Fields/TextField/textfield.cpp widgets/editor/Fields/TextField/textfield.ui
        widgets/editor/FieldConnection/fieldconnection.h widgets/editor/FieldConnection/fieldconnection.cpp widgets/editor/FieldConnection/fieldconnection.ui
        widgets/editor/Fields/CharacterField/characterfield.h widgets/editor/Fields/CharacterField/characterfield.cpp widgets/editor/Fields/CharacterField/characterfield.ui

        widgets/editor/EditorTools/Settings/listsettings.h widgets/editor/EditorTools/Settings/listsettings.cpp
        widgets/editor/EditorTools/Settings/effectsettings.h widgets/editor/EditorTools/Settings/effectsettings.cpp
        widgets/editor/EditorTools/Settings/presetsettings.h widgets/editor/EditorTools/Settings/presetsettings.cpp
        widgets/editor/EditorTools/Settings/effectsettings.ui
        widgets/editor/EditorTools/Settings/presetsettings.ui
        widgets/editor/EditorTools/Settings/listsettings.ui
        widgets/editor/EditorTools/Settings/settingsoption.h widgets/editor/EditorTools/Settings/settingsoption.cpp widgets/editor/EditorTools/Settings/settingsoption.ui

        widgets/editor/Fields/ListField/listfield.h widgets/editor/Fields/ListField/listfield.cpp widgets/editor/Fields/ListField/listfield.ui

        widgets/editor/EditorTools/EffectsDropdown/effectsdropdown.h widgets/editor/EditorTools/EffectsDropdown/effectsdropdown.cpp widgets/editor/EditorTools/EffectsDropdown/effectsdropdown.ui

        data/Presets/preset.h data/Presets/preset.cpp
        data/Fields/FieldTypes.h

        widgets/tabs/NewTab/newtab.h widgets/tabs/NewTab/newtab.cpp widgets/tabs/NewTab/newtab.ui
        widgets/tabs/TabWindow/tabwindow.h widgets/tabs/TabWindow/tabwindow.cpp widgets/tabs/TabWindow/tabwindow.ui





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
target_link_libraries(TexT_Editor PRIVATE Qt6::WebEngineWidgets)

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
