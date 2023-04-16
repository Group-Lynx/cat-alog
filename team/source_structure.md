# 源码结构

## 目录

- [源码结构](#源码结构)
  - [目录](#目录)
  - [文件结构](#文件结构)
  - [头文件格式](#头文件格式)
  - [源码文件格式](#源码文件格式)
  - [`CMakeLists.txt` 配置](#cmakeliststxt-配置)


## 文件结构

- `CMakeLists.txt` 是 CMake 的配置文件，它指导项目的构建、测试、编译管理。
- `include/class_name.h` 是 `ClassName` 类的声明文件。
- `src/class_name.cpp` 是 `ClassName` 类的实现文件。
- `src/main.cpp` 是程序的主体，功能的调用都在此实现。

```txt
cat-alog/
├── CMakeLists.txt
├── README.md
├── include/
│   └── 头文件.h
├── project/
│   └── 工程指导文件.md
├── src/
│   ├── main.cpp
│   └── 源码文件.cpp
└── team/
    └── 团队管理文件.md
```

## 头文件格式

```cpp
// course.h
#ifndef COURSE_H
#define COURSE_H

class Course
{
    // Properties
private:
    WeekTime classStartTime;
    WeekTime classEndTime;
    
    // Methods
public:
    void GetCourseInfo();
};

#endif
```

## 源码文件格式

```cpp
// course.cpp
#include "course.h"

void Course::GetCourseInfo()
{
    // do something
}

```

## `CMakeLists.txt` 配置

- 如果提示没有 `nmake`，在项目根目录下运行 `cmake -G "MinGW Makefiles" -DCMAKE_C_COMPILER=gcc.exe -DCMAKE_CXX_COMPILER=g++.exe .`
- 每次添加新的 `cpp` 文件都要记得添加到 `SOURCE` 变量中

```cmake
# 设定支持的 CMake 最低的版本
cmake_minimum_required(VERSION 3.10)

# 设置项目名称为 catalog
project(catalog)

# 将源码文件添加到 SROUCE 变量中
set(SOURCES
    src/main.cpp
)

# 设置 include 目录
include_directories(include)

# 将 SOURCE 源码编译为可执行文件 PROJECT_NAME（也就是 catalog.exe）
add_executable(${PROJECT_NAME} ${SOURCES})
```
