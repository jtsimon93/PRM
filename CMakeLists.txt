cmake_minimum_required(VERSION 3.28)
project(PRM)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Use vcpkg toolchain file if VCPKG_ROOT is defined
if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()

# Find Qt and sqlite3 packages
find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)
find_package(unofficial-sqlite3 CONFIG REQUIRED)
find_path(SQLITE_MODERN_CPP_INCLUDE_DIRS "sqlite_modern_cpp.h")

# Automatically include all source and header files
file(GLOB_RECURSE PRM_SOURCES src/*.cpp include/*.h)

# Manually add main.cpp from the root directory
list(APPEND PRM_SOURCES ${CMAKE_SOURCE_DIR}/main.cpp)

# Add the executable
add_executable(PRM ${PRM_SOURCES})

# Include directories
target_include_directories(PRM PRIVATE ${SQLITE_MODERN_CPP_INCLUDE_DIRS})

# Link the Qt and sqlite3 libraries
target_link_libraries(PRM Qt6::Core Qt6::Gui Qt6::Widgets unofficial::sqlite3::sqlite3)
