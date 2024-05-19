cmake_minimum_required(VERSION 3.28)
project(PRM)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Check if Qt6_DIR is set, otherwise fall back to default
if(NOT DEFINED Qt6_DIR)
    message(FATAL_ERROR "Qt6_DIR is not set. Please set Qt6_DIR to the Qt6 installation path.")
endif()

list(APPEND CMAKE_PREFIX_PATH "${Qt6_DIR}")

find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)

add_executable(PRM main.cpp)
target_link_libraries(PRM Qt6::Core Qt6::Gui Qt6::Widgets)
