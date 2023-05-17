# 设定支持的 CMake 最低的版本
cmake_minimum_required(VERSION 3.10)

# 设置项目名称为 catalog
project(catalog)

# 指定 CMake 使用 MinGW Makefiles
set(CMAKE_GENERATOR "MinGW Makefiles")
set(CMAKE_C_COMPILER "gcc.exe")
set(CMAKE_CXX_COMPILER "g++.exe")

# 将源码文件添加到 SROUCE 变量中
set(SOURCES
    src/main.cpp
    src/List.cpp
    src/Node.cpp
)

# 设置 include 目录
include_directories(include)

# 将 SOURCE 源码编译为可执行文件 PROJECT_NAME（也就是 catalog.exe）
add_executable(${PROJECT_NAME} ${SOURCES})
