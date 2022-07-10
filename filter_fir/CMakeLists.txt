cmake_minimum_required(VERSION 3.14)

project(filter_fir LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_library(filter_fir SHARED
  filter_fir_global.h
  filter_fir.cpp
  filter_fir.h
)

target_link_libraries(filter_fir Qt${QT_VERSION_MAJOR}::Core)
target_compile_definitions(filter_fir PRIVATE FILTER_FIR_LIBRARY)
