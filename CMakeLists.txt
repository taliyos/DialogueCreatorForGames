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
find_package(Qt6 REQUIRED COMPONENTS Multimedia)

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

        widgets/editor/EditorTools/Settings/SettingsOption/settingsoption.h widgets/editor/EditorTools/Settings/SettingsOption/settingsoption.cpp widgets/editor/EditorTools/Settings/SettingsOption/settingsoption.ui

        widgets/editor/EditorTools/Settings/ListSettings/listsettings.h widgets/editor/EditorTools/Settings/ListSettings/listsettings.cpp
        widgets/editor/EditorTools/Settings/EffectSettings/effectsettings.h widgets/editor/EditorTools/Settings/EffectSettings/effectsettings.cpp
        widgets/editor/EditorTools/Settings/PresetSettings/presetsettings.h widgets/editor/EditorTools/Settings/PresetSettings/presetsettings.cpp
        widgets/editor/EditorTools/Settings/EffectSettings/effectsettings.ui
        widgets/editor/EditorTools/Settings/PresetSettings/presetsettings.ui
        widgets/editor/EditorTools/Settings/ListSettings/listsettings.ui

        widgets/editor/Fields/ListField/listfield.h widgets/editor/Fields/ListField/listfield.cpp widgets/editor/Fields/ListField/listfield.ui

        widgets/editor/EditorTools/EffectsDropdown/effectsdropdown.h widgets/editor/EditorTools/EffectsDropdown/effectsdropdown.cpp widgets/editor/EditorTools/EffectsDropdown/effectsdropdown.ui

        data/Presets/preset.h data/Presets/preset.cpp
        data/Fields/FieldTypes.h

        widgets/tabs/TabWindow/tabwindow.h widgets/tabs/TabWindow/tabwindow.cpp widgets/tabs/TabWindow/tabwindow.ui
        widgets/tabs/ClosableTab/closabletab.h widgets/tabs/ClosableTab/closabletab.cpp widgets/tabs/ClosableTab/closabletab.ui
        widgets/tabs/TabableWidget/tabablewidget.h widgets/tabs/TabableWidget/tabablewidget.cpp widgets/tabs/TabableWidget/tabablewidget.ui

        widgets/editor/Fields/InputOpenField/inputopenfield.h widgets/editor/Fields/InputOpenField/inputopenfield.cpp widgets/editor/Fields/InputOpenField/inputopenfield.ui
        widgets/editor/Fields/InputListField/inputlistfield.h widgets/editor/Fields/InputListField/inputlistfield.cpp widgets/editor/Fields/InputListField/inputlistfield.ui
        data/Fields/MainFields/input/inputlistdata.h data/Fields/MainFields/input/inputlistdata.cpp
        widgets/editor/EditorTools/Settings/FieldSettings/fieldsettings.h widgets/editor/EditorTools/Settings/FieldSettings/fieldsettings.cpp widgets/editor/EditorTools/Settings/FieldSettings/fieldsettings.ui
        widgets/editor/EditorTools/Settings/InputListSettings/inputlistsettings.h widgets/editor/EditorTools/Settings/InputListSettings/inputlistsettings.cpp widgets/editor/EditorTools/Settings/InputListSettings/inputlistsettings.ui
        widgets/editor/EditorTools/Settings/InputListSettingsConfig/inputlistsettingsconfig.h widgets/editor/EditorTools/Settings/InputListSettingsConfig/inputlistsettingsconfig.cpp widgets/editor/EditorTools/Settings/InputListSettingsConfig/inputlistsettingsconfig.ui



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
target_link_libraries(TexT_Editor PRIVATE Qt6::Multimedia)

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

cmake_path(GET CMAKE_CURRENT_SOURCE_DIR PARENT_PATH PARENT_DIR)
set(DUCKX_LIBRARY "${PARENT_DIR}/build-DuckX-Desktop_Qt_${QT_VERSION_MAJOR}_${QT_VERSION_MINOR}_${QT_VERSION_PATCH}_MSVC2019_64bit-Debug/duckx.lib")
target_link_libraries(TexT_Editor PRIVATE ${DUCKX_LIBRARY})
target_include_directories(TexT_Editor PUBLIC "${PARENT_DIR}/DuckX/include")
