cmake_minimum_required(VERSION 3.24)
project(320PhotoEditor)

set(CMAKE_CXX_STANDARD 17)
set(SOURCE_FILES main.cpp)
include_directories(${SFML_INCLUDE_DIRS})
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

include_directories(.)
include_directories(GUI)
include_directories(Layer)
include_directories(Tool)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "/Users/davidoakes/CS320/320PhotoEditor/bin")

add_executable(320PhotoEditor
        GUI/ButtonElement.cpp
        GUI/ButtonElement.h
        GUI/GUIContainer.cpp
        GUI/GUIContainer.h
        GUI/GUIElement.cpp
        GUI/GUIElement.h
        GUI/PanelElement.cpp
        GUI/PanelElement.h
        Layer/Layer.cpp
        Layer/Layer.h
        Layer/LayerManager.cpp
        Layer/LayerManager.h
        Tool/TestTool.cpp
        Tool/TestTool.h
        Tool/Tool.cpp
        Tool/Tool.h
        Tool/ToolManager.cpp
        Tool/ToolManager.h
        Application.cpp
        Application.h
        Common.cpp
        Common.h
        InputListener.cpp
        InputListener.h
        Main.cpp)

target_link_libraries(320PhotoEditor sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
