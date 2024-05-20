cmake_minimum_required(VERSION 3.28)
project(PRM)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Use vcpkg toolchain file if VCPKG_ROOT is defined
if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()

# Find Qt and sqlite3 packages
find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)
find_package(unofficial-sqlite3 CONFIG REQUIRED)
find_path(SQLITE_MODERN_CPP_INCLUDE_DIRS "sqlite_modern_cpp.h")

# Fetch Boost.DI
include(FetchContent)
FetchContent_Declare(
        boost_di
        GIT_REPOSITORY https://github.com/boost-ext/di.git
        GIT_TAG cpp14
)
FetchContent_MakeAvailable(boost_di)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/include/models)
include_directories(${CMAKE_SOURCE_DIR}/include/repositories)
include_directories(${CMAKE_SOURCE_DIR}/include/services)
include_directories(${SQLITE_MODERN_CPP_INCLUDE_DIRS})

# Automatically include all source and header files
file(GLOB_RECURSE PRM_HEADERS
        ${CMAKE_SOURCE_DIR}/include/*.h
        ${CMAKE_SOURCE_DIR}/include/models/*.h
        ${CMAKE_SOURCE_DIR}/include/repositories/*.h
        ${CMAKE_SOURCE_DIR}/include/services/*.h
        ${CMAKE_SOURCE_DIR}/include/ui/*.h
)

file(GLOB_RECURSE PRM_SOURCES
        ${CMAKE_SOURCE_DIR}/src/*.cpp
        ${CMAKE_SOURCE_DIR}/src/models/*.cpp
        ${CMAKE_SOURCE_DIR}/src/repositories/*.cpp
        ${CMAKE_SOURCE_DIR}/src/services/*.cpp
        ${CMAKE_SOURCE_DIR}/src/ui/*.cpp
)

# Manually add main.cpp from the root directory
list(APPEND PRM_SOURCES ${CMAKE_SOURCE_DIR}/main.cpp)

# Add the executable
add_executable(PRM ${PRM_SOURCES} ${PRM_HEADERS})

# Link the Qt and sqlite3 libraries
target_link_libraries(PRM Qt6::Core Qt6::Gui Qt6::Widgets unofficial::sqlite3::sqlite3)

# Ensure Boost.DI is available
target_include_directories(PRM PRIVATE ${boost_di_SOURCE_DIR}/include)
