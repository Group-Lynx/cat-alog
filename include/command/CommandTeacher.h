#ifndef COMMAND_TCH_H
#define COMMAND_TCH_H

#include "../command/CommandAdmin.h"

namespace TCH
{
    void Construct(CTree& _root);
    
    void None();
    void Help();
    void Mine();
    void View();
    void Detail();
    void Create();
    void Delete();
    
    void Pswd();
    void Logout();
    void Exit();
}

// 无效命令。
void TCH::None()
{
    IO::ERROR("未知命令，输入 `help` 以获取更多信息。");
}

// 构建命令树。
void TCH::Construct(CTree& _root)
{
    _root.Grow(std::make_unique<CTree>(CTree("help", Help)));
    _root.Grow(std::make_unique<CTree>(CTree("mine", Mine)));
    _root.Grow(std::make_unique<CTree>(CTree("view", View)));
    _root.Grow(std::make_unique<CTree>(CTree("detail", Detail)));
    _root.Grow(std::make_unique<CTree>(CTree("create", Create)));
    _root.Grow(std::make_unique<CTree>(CTree("delete", Delete)));
    
    _root.Grow(std::make_unique<CTree>(CTree("pswd", Pswd)));
    _root.Grow(std::make_unique<CTree>(CTree("logout", Logout)));
    _root.Grow(std::make_unique<CTree>(CTree("exit", Exit)));
}

// 帮助信息。
void TCH::Help()
{
    IO::PRINT("可用命令：");
    IO::PRINT("  课程管理：");
    IO::PRINT("    mine    - 显示我的课程");
    IO::PRINT("    view    - 显示所有课程");
    IO::PRINT("    detail  - 显示课程细节");
    IO::PRINT("    create  - 创建课程");
    IO::PRINT("    delete  - 删除课程");
    IO::PRINT("  其他命令：");
    IO::PRINT("    help    - 显示本帮助信息");
    IO::PRINT("    pswd    - 更改密码");
    IO::PRINT("    logout  - 登出当前用户");
    IO::PRINT("    exit    - 退出程序");
}

// 查看我的课程。
void TCH::Mine()
{
    Teacher me = DM::GetTeacher(VAR::currentUser.ID());
    List<ID_t> teaching = me.Taught();
    
    IO::PRINT("我的课程：");
    for (int i = 0; i < teaching.Length(); i++)
    {
        IO::PRINT(ADM::COURSE::Peek(teaching[i]));
    }
}

// 查看所有课程。
void TCH::View()
{
    List<Course> courses = DM::AllCourses();
    IO::PRINT("所有课程");
    for (int i = 0; i < courses.Length(); i++)
    {
        IO::PRINT("  - ", ADM::COURSE::Peek(courses[i].ID()));
    }
}

// 查看课程详情。
void TCH::Detail()
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

// 创建课程。
void TCH::Create()
{
FLAG_FetchCourseInfo:
    ID_t cid = -1;
    IO::INPUT("课程 ID") >> cid;
    
    if (DM::HasCourse(cid))
    {
        IO::ERROR("ID ", cid, "的课程已存在，运行失败。");
        return;
    }
    
    std::string name = IO::CLINE("课程名称");
    Size_t capacity = 0;
    IO::INPUT("课程容量") >> capacity;
    
    IO::PRINT("课程 ID：", cid);
    IO::PRINT("课程名称：", name);
    IO::PRINT("课程容量：", capacity);
    if (IO::CHECK(true, "已全部确认？") == false)
    {
        if (IO::CHECK(false, "重新输入信息？") == false)
        {
            IO::MESSG("本次运行失败。");
            return;
        }
        goto FLAG_FetchCourseInfo;
    }
    
    DM::AddCourse(Course(cid, name, capacity, VAR::currentUser.ID()));
    IO::MESSG("课程已创建。");
}

// 删除课程。
void TCH::Delete()
{
    ID_t cid = -1;
    IO::INPUT("课程 ID") >> cid;
    
    Course course = DM::GetCourse(cid);
    
    if (course.Teacher() != VAR::currentUser.ID())
    {
        IO::ERROR("您不是该课程的课任教师，运行失败。");
        return;
    }
    
    if (IO::CHECK(false, "确认删除？") == false)
    {
        IO::MESSG("删除已取消。");
        return;
    }
    
    DM::RemoveCourse(cid);
    IO::MESSG("课程已删除。");
}

// 修改密码。
void TCH::Pswd()
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
void TCH::Logout()
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
void TCH::Exit()
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