#ifndef COMMAND_CMD_H
#define COMMAND_CMD_H

#include "../data/DataManip.h"

#include "../utility/Crypto.h"
#include "../utility/IOHandle.h"
#include "../utility/ValidString.h"
#include "../utility/LynType.h"

#include "../data/GlobalVariable.h"

namespace CMD
{
    void Construct(CTree& _root);
    
    void None();
    void Help();
    void Info();
    void Color();
    void Login();
    void Exit();
}

// 构建命令树。
void CMD::Construct(CTree& _root)
{
    _root.Grow(std::make_unique<CTree>(CTree("help", Help)));
    _root.Grow(std::make_unique<CTree>(CTree("info", Info)));
    _root.Grow(std::make_unique<CTree>(CTree("color", Color)));
    _root.Grow(std::make_unique<CTree>(CTree("login", Login)));
    _root.Grow(std::make_unique<CTree>(CTree("exit", Exit)));
}

// 未知命令。
void CMD::None()
{
    IO::ERROR("未知命令，输入 `help` 以获取更多信息。");
}

// 帮助信息。
void CMD::Help()
{
    IO::PRINT("可用命令：");
    IO::PRINT("  help   - 显示本帮助信息");
    IO::PRINT("  info   - 显示程序信息");
    IO::PRINT("  color  - 变更颜色设置");
    IO::PRINT("  login  - 登录账户");
    IO::PRINT("  exit   - 退出程序");
}

// 程序信息。
void CMD::Info()
{
    IO::PRINT(" ___________");
    IO::PRINT("|           |   程序名称: Catalog");
    IO::PRINT("|  catalog  |   版本: 1.0.3");
    IO::PRINT("| __        |   信息: C 程序设计");
    IO::PRINT(" /  /_______|   主题: 选课管理系统");
    IO::PRINT(" \\__________|   算法: 链表、文件处理");
    IO::PRINT("");
}

// 切换颜色模式。
void CMD::Color()
{
    bool colored = IO::FlipColorStatus();
    IO::MESSG("颜色设置 ", colored ? "启用" : "未启用", "。");
}

// 登录。
void CMD::Login()
{
    ID_t uid = -1;
    std::string input;
    IO::INPUT("用户 ID") >> input;
    if (VS::IsNumber(input)) { uid = std::stoll(input); }
    
    if (!DM::HasUser(uid))
    {
        IO::ERROR("查询不到 ID ", uid, "的用户，运行失败。");
        return;
    }
    
    User& user = DM::GetUser(uid);
    
    std::string pswd;
    for (int attempt = 0; attempt < 3; attempt++)
    {
        pswd = IO::SECRT("密码");
        if (user.Authenticate(pswd))
        {
            IO::MESSG("登陆成功，欢迎 ", user.Name(), "！");
            VAR::currentUser = user;
            return;
        }
        else
        {
            IO::ALERT("密码错误,剩余 ", 2 - attempt, " 次尝试机会");
        }
    }
    IO::ERROR("已尝试3次，密码错误，操作终止。");
}

// 退出程序。
void CMD::Exit()
{
    if (IO::CHECK(false, "您确认退出程序码？") == false)
    {
        IO::MESSG("退出已取消");
        return;
    }
    IO::MESSG("程序中止。。。");
    VAR::isRunning = false;
}

#endif