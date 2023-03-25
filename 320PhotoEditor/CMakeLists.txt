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
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "/Users/davidoakes/CS320/320PhotoEditor/bin")


add_executable(320PhotoEditor
        GUI/ButtonElement.cpp
        GUI/ButtonElement.h
        GUI/ColorPickerElement.cpp
        GUI/ColorPickerElement.h
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
        Tool/FilterTool.cpp
        Tool/FilterTool.h
        Tool/MosaicTool.cpp
        Tool/MosaicTool.h
        Tool/PaintTool.cpp
        Tool/PaintTool.h
        Tool/SelectTool.cpp
        Tool/SelectTool.h
        Tool/TestTool.cpp
        Tool/TestTool.h
        Tool/Tool.cpp
        Tool/Tool.h
        Tool/ToolManager.cpp
        Tool/ToolManager.h
        Tool/Zoom.cpp
        Tool/Zoom.h
        Application.cpp
        Application.h
        ApplicationMenu.cpp
        ApplicationMenu.h
        AssetManager.cpp
        AssetManager.h
        Common.cpp
        Common.h
        ComputeShader.cpp
        ComputeShader.h
        InputListener.cpp
        InputListener.h
        WindowListener.cpp
        WindowListener.h
        Main.cpp Tool/PaintTool.cpp GUI/ColorPickerElement.cpp Tool/FilterTool.cpp Tool/FilterTool.h Tool/Zoom.cpp Tool/Zoom.h)

target_link_libraries(320PhotoEditor sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

