#ifndef COMMAND_STU_H
#define COMMAND_STU_H

#include "../command/CommandAdmin.h"

namespace STU
{
    void Construct(CTree& _root);
    
    void None();
    void Help();
    void Mine();
    void View();
    void Detail();
    void Take();
    void Drop();
    
    void Pswd();
    void Logout();
    void Exit();
}

// 无效命令。
void STU::None()
{
    IO::ERROR("未知命令，输入 `help` 以获取更多信息。");
}

// 构建命令树。
void STU::Construct(CTree& _root)
{
    _root.Grow(std::make_unique<CTree>(CTree("help", Help)));
    _root.Grow(std::make_unique<CTree>(CTree("mine", Mine)));
    _root.Grow(std::make_unique<CTree>(CTree("view", View)));
    _root.Grow(std::make_unique<CTree>(CTree("detail", Detail)));
    _root.Grow(std::make_unique<CTree>(CTree("take", Take)));
    _root.Grow(std::make_unique<CTree>(CTree("drop", Drop)));
    
    _root.Grow(std::make_unique<CTree>(CTree("pswd", Pswd)));
    _root.Grow(std::make_unique<CTree>(CTree("logout", Logout)));
    _root.Grow(std::make_unique<CTree>(CTree("exit", Exit)));
}

// 帮助信息。
void STU::Help()
{
    IO::PRINT("可用命令：");
    IO::PRINT("  课程管理：");
    IO::PRINT("    mine    - 显示我的课程");
    IO::PRINT("    view    - 显示所有课程");
    IO::PRINT("    detail  - 显示课程细节");
    IO::PRINT("    take    - 选课");
    IO::PRINT("    drop    - 退课");
    IO::PRINT("  其他命令：");
    IO::PRINT("    help    - 显示本帮助信息");
    IO::PRINT("    pswd    - 更改密码");
    IO::PRINT("    logout  - 登出当前用户");
    IO::PRINT("    exit    - 退出程序");
}

// 查看我的课程。
void STU::Mine()
{
    Student me = DM::GetStudent(VAR::currentUser.ID());
    List<ID_t> selected = me.Selected();
    
    IO::PRINT("选择课程：");
    for (int i = 0; i < selected.Length(); i++)
    {
        IO::PRINT("  - ", ADM::COURSE::Peek(selected[i]));
    }
}

// 查看所有课程。
void STU::View()
{
    List<Course> courses = DM::AllCourses();
    IO::PRINT("所有课程：");
    for (int i = 0; i < courses.Length(); i++)
    {
        IO::PRINT("  - ", ADM::COURSE::Peek(courses[i].ID()));
    }
}

// 查看课程详情。
void STU::Detail()
{
    ID_t cid = -1;
    IO::INPUT("课程 ID") >> cid;
    if (!DM::HasCourse(cid))
    {
        IO::ERROR("查询不到 ID ", cid, "的课程，运行失败。");
        return;
    }
    
    Course course = DM::GetCourse(cid);
    ADM::COURSE::Display(cid);
}

// 选课。
void STU::Take()
{
    ID_t cid = -1;
    IO::INPUT("课程 ID") >> cid;
    
    if (!DM::HasCourse(cid))
    {
        IO::ERROR("查询不到 ID ", cid, "的课程，运行失败。");
        return;
    }
    
    ADM::COURSE::Display(cid);
    
    Course course = DM::GetCourse(cid);
    if (course.IsFull())
    {
        IO::ERROR("课程已满，运行失败。");
        return;
    }
    
    if (IO::CHECK(true, "确认选课？") == false)
    {
        IO::MESSG("选课已取消。");
        return;
    }
    
    DM::Enroll(VAR::currentUser.ID(), cid);
    IO::MESSG("选课成功。");
}

// 退课。
void STU::Drop()
{
    ID_t cid = -1;
    IO::INPUT("课程 ID") >> cid;
    
    if (!DM::HasCourse(cid))
    {
        IO::ERROR("查询不到 ID ", cid, "的课程，运行失败。");
        return;
    }
    
    ADM::COURSE::Display(cid);
    
    Course course = DM::GetCourse(cid);
    
    if (IO::CHECK(false, "确认退课？") == false)
    {
        IO::MESSG("退课已取消");
        return;
    }
    
    DM::Remove(VAR::currentUser.ID(), cid);
    IO::MESSG("退课成功。");
}

// 修改密码。
void STU::Pswd()
{
    std::string oldpswd = IO::SECRT("旧密码");
    
    if (VAR::currentUser.Authenticate(oldpswd) == false)
    {
        IO::ERROR("密码错误");
        return;
    }
    
    std::string newpswd = IO::SECRT("新密码");
    std::string cfmpswd = IO::SECRT("确认密码");
    
    if (newpswd != cfmpswd)
    {
        IO::ERROR("密码不匹配。");
        return;
    }
    
    if (newpswd == SSP::Encrypt(""))
    {
        IO::MESSG("密码未改变。");
        return;
    }
    
    User& user = DM::GetUser(VAR::currentUser.ID());
    user.ChangePassword(oldpswd, newpswd);
    VAR::currentUser = user;
    
    IO::MESSG("密码已改变。");
}

// 退出登录。
void STU::Logout()
{
    if (IO::CHECK(false, "确认登出？") == false)
    {
        IO::MESSG("登出已取消");
        return;
    }
    IO::MESSG("成功登出，再见 ", VAR::currentUser.Name(), "。");
    VAR::currentUser = UNKOWN_USER;
}

// 退出程序。
void STU::Exit()
{
    if (IO::CHECK(false, "确认退出程序？") == false)
    {
        IO::MESSG("退出已取消");
        return;
    }
    if (IO::CHECK(false, "再次确认，退出程序？") == false)
    {
        IO::MESSG("退出已取消");
        return;
    }
    IO::MESSG("程序中止。。。");
    VAR::isRunning = false;
}

#endif