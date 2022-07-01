cmake_minimum_required(VERSION 3.23)

project(Qt_ScreenShot_final VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 6.2 COMPONENTS Quick REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS PrintSupport)
find_package(Qt6 REQUIRED COMPONENTS Gui)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Qml)

qt_add_resources(qml_FILES qml.qrc)
qt_add_executable(appQt_ScreenShot_final

    capture.cpp
    copypaintitem.cpp
    filter.cpp
    freecapture.cpp
    gifwidget.cpp
    longshot.cpp
    mosaic.cpp
    mylabel.cpp
    painteditem.cpp
    recscreen.cpp
    RecScreen.h
    share.cpp
    main.cpp
#    elementgroup.h
#    RecScreen.h
    ${qml_FILES}
)

qt_add_qml_module(appQt_ScreenShot_final
    URI Qt_ScreenShot_final
    VERSION 1.0
    QML_FILES
)

set_target_properties(appQt_ScreenShot_final PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(appQt_ScreenShot_final
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(appQt_ScreenShot_final
    PRIVATE Qt6::Quick)
target_link_libraries(appQt_ScreenShot_final PRIVATE Qt6::Widgets)

target_link_libraries(appQt_ScreenShot_final PRIVATE Qt6::PrintSupport)

target_link_libraries(appQt_ScreenShot_final PRIVATE Qt6::Gui)

target_link_libraries(appQt_ScreenShot_final PRIVATE Qt6::Core)

target_link_libraries(appQt_ScreenShot_final PRIVATE Qt6::Qml)
