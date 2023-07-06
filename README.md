# 【提示】仓库存档

**这 C/C++ 程序设计的代码仓库，现作业已提交，该仓库就此存档。**

# Catalog - 猫记选课

## 目录

- [Catalog - 猫记选课](#catalog---猫记选课)
  - [目录](#目录)
  - [项目结构](#项目结构)
  - [编译、构建](#编译构建)
    - [使用系统安装的 `g++`](#使用系统安装的-g)
    - [使用项目打包的 `g++`](#使用项目打包的-g)
  - [运行](#运行)
    - [在终端启动](#在终端启动)
    - [双击启动](#双击启动)
  - [常见问题](#常见问题)
    - [中文乱码](#中文乱码)
    - [出现 `\033[96m`](#出现-03396m)
  - [命令](#命令)
    - [用户与密码](#用户与密码)
    - [未登录](#未登录)
    - [管理员](#管理员)
    - [学生](#学生)
    - [老师](#老师)
  - [测试](#测试)
    - [首次运行](#首次运行)
    - [使用已构建好的数据库](#使用已构建好的数据库)
    - [模拟数据被污染](#模拟数据被污染)

## 项目结构

```txt
catalog/                      |  项目根目录
├── include/                  |  头文件目录
│   ├── command/              |  命令相关
│   │   ├── CommandAdmin.h    |    管理员命令
│   │   ├── CommandGeneral.h  |    基础命令
│   │   ├── CommandStudent.h  |    学生命令
│   │   ├── CommandTeacher.h  |    老师命令
│   │   └── CommandTree.h     |    命令树
│   ├── data/                 |  数据管理
│   │   ├── DMException.h     |    数据异常
│   │   ├── DataManip.h       |    数据操纵器
│   │   └── GlobalVariable.h  |    全局变量
│   ├── object/               |  基础对象
│   │   ├── Course.h          |    课程
│   │   ├── Student.h         |    学生
│   │   ├── Teacher.h         |    教师
│   │   └── User.h            |    用户
│   ├── struct/               |  数据结构
│   │   ├── List.h            |    链表
│   │   └── Node.h            |    节点
│   └── utility/              |  工具集合
│       ├── Crypto.h          |    加密算法
│       ├── FileHandle.h      |    文件处理
│       ├── IOHandle.h        |    读写处理
│       ├── LynType.h         |    自定义类型
│       └── ValidString.h     |    合法字符串
├── release/                  |  发行程序
│   ├── catalog.exe           |    程序主体
│   ├── root.lyn              |    根数据
│   ├── course.lyn            |    课程数据
│   └── user.lyn              |    用户数据
├── src/                      |  源代码
│   └── main.cpp              |    主代码
└── test/                     |  测试区域
    └── ...                   |    ......
```

## 编译与构建

该方法假定您的计算机上有 `g++` 编译器，并已添加到系统 `PATH` 中。

```bash
# 首先，打开终端，切换至 catalog 项目目录
$ cd ./catalog/
# 编译并生成 catalog.exe，放置在当前目录的 release 文件夹下
$ g++ ./src/main.cpp -o ./release/catalog.exe
```

## 运行

该项目有两种运行方式，终端启动或者双击启动。

### 在终端启动

```bash
# 切换至 catalog.exe 所在的目录
$ cd ./release
# 执行 catalog.exe
$ ./catalog.exe
```

### 双击启动

打开文件资源管理器，前往 `release` 文件夹，双击启动 `catalog.exe`。

## 常见问题

### 中文乱码

该项目使用的中文编码是 GB2312。

**解决方案**：遗憾的是我们并不能准确地断言解决方法，因为中文在不同的编码体系中编码方式不同，在不同的终端上也表现不同。

### 出现 `\033[96m`

这是我们对终端的颜色修饰。经过测试，我们发现这样的颜色修饰方式在一些较老的系统上无法正确展现。

**解决方案**：在启动程序后输入 `color` 来关闭颜色化输出。

## 命令

这里列出了程序所支持的所有命令，命令随身份的改变而改变。同时，您也可以在程序中输入 `help` 来查看帮助。

### 用户与密码

其余未指明的账号其密码与 ID 相同。

| 身份 | 用户 ID | 密码 |
|:-----|:-------|:-----|
| 管理员 | 0 | admin |

### 未登录

```txt
unidentified>
├── help   - 帮助信息
├── info   - 显示程序信息
├── color  - 变更颜色模式
├── login  - 登录账户
└── exit   - 退出程序
```

### 管理员

```txt
administrator>
├── help    - 帮助信息
├── save    - 保存信息
├── pswd    - 变更密码
├── script  - 执行脚本
├── logout  - 登出账户
├── exit    - 退出程序
├── user    - 进行用户管理
│   ├── help    - 帮助信息
│   ├── pswd    - 变更用户密码
│   ├── view    - 显示所有用户
│   ├── detail  - 显示用户详情*
│   ├── create  - 创建用户*
│   └── delete  - 删除用户*
└── course  - 进行课程管理
    ├── help    - 帮助信息
    ├── view    - 显示所有课程
    ├── detail  - 显示课程详情*
    ├── create  - 创建课程*
    ├── delete  - 删除课程*
    ├── assign  - 为指定教师分配课程*
    ├── enroll  - 为指定学生选择课程*
    └── remove  - 为指定学生退选课程*
对于加 * 的命令，可以使用 -arg 来执行参数传递
user detail -arg [user ID]
user create -arg [user type] [user ID] [user name]
user delete -arg [user ID]
course detail -arg [course ID]
course create -arg [course ID] [capacity] [teacher ID] [name]
course delete -arg [course ID]
course assign -arg [course ID] [teacher ID]
course enroll -arg [course ID] [student ID]
course remove -arg [course ID] [student ID]
```

### 学生

```txt
mine    - 显示已选课程
view    - 显示所有课程
detail  - 获取课程详情
take    - 选课
drop    - 退课

help    - 获取帮助
pswd    - 变更密码
logout  - 登出账户
exit    - 退出程序
```

### 老师

```txt
mine    - 显示已授课程
view    - 显示所有课程
detail  - 获取课程详情
create  - 创建课程
delete  - 删除课程

help    - 获取帮助
pswd    - 变更密码
logout  - 登出账户
exit    - 退出程序
```

## 引用

- 
