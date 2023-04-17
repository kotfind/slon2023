cmake_minimum_required(VERSION 3.16)

project(polygons LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

set(CMAKE_CXX_FLAGS_DEBUG "-fsanitize=undefined,address -g3 -O0")

find_package(Qt6 REQUIRED
    Core
    Widgets
)

qt_standard_project_setup()

add_executable(polygons
    main.cpp

    MainWindow.cpp

    Polygon.cpp
    PolygonModel.cpp
    PolygonGraphicsItem.cpp

    EditableTableWidget.cpp

)

target_link_libraries(polygons
    Qt6::Core
    Qt6::Widgets
)
