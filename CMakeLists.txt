cmake_minimum_required(VERSION 3.24)
project(CourseProject)

set(CMAKE_CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/qt/lib/cmake")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(CourseProject main.cpp mainwindow.cpp mainwindow.ui Model.cpp View.cpp Controller.cpp InfoTree.cpp aboutwindow.cpp Application.cpp)
target_link_libraries(CourseProject
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

