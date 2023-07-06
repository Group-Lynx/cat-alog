#ifndef COMMAND_ADM_H
#define COMMAND_ADM_H

#include "../data/DataManip.h"

#include "../utility/IOHandle.h"
#include "../utility/ValidString.h"

#include "../data/GlobalVariable.h"

bool Execute(std::function<void()> _func);

namespace ADM
{
    void Construct(CTree& _root);
    
    void None();
    void Help();
    void Save();
    void Script();
    void Pswd();
    void Logout();
    void Exit();
    
    namespace USER
    {
        void Help();
        void View();
        void Pswd();
        void Detail();
        void Create();
        void Delete();
        
        void Display(ID_t _uid);
        std::string Peek(ID_t _uid);
        
        void DetailArg();
        void CreateArg();
        void DeleteArg();
    }
    
    namespace COURSE
    {
        void Help();
        void View();
        void Detail();
        void Create();
        void Delete();
        void Assign();
        void Enroll();
        void Remove();
        
        void Display(ID_t _cid);
        std::string Peek(ID_t _cid);
        
        void DetailArg();
        void CreateArg();
        void DeleteArg();
        void AssignArg();
        void EnrollArg();
        void RemoveArg();
    }
}

// 构建命令树
void ADM::Construct(CTree& _root)
{
    std::unique_ptr<CTree> _user = std::make_unique<CTree>(CTree("user", USER::Help));
    _user->Grow(std::make_unique<CTree>(CTree("help", USER::Help)));
    _user->Grow(std::make_unique<CTree>(CTree("view", USER::View)));
    _user->Grow(std::make_unique<CTree>(CTree("pswd", USER::Pswd)));
    
    std::unique_ptr<CTree> _usr_detail = std::make_unique<CTree>(CTree("detail", USER::Detail));
    _usr_detail->Grow(std::make_unique<CTree>(CTree("-arg", USER::DetailArg)));
    _user->Grow(std::move(_usr_detail));
    
    std::unique_ptr<CTree> _usr_create = std::make_unique<CTree>(CTree("create", USER::Create));
    _usr_create->Grow(std::make_unique<CTree>(CTree("-arg", USER::CreateArg)));
    _user->Grow(std::move(_usr_create));
    
    std::unique_ptr<CTree> _usr_delete = std::make_unique<CTree>(CTree("delete", USER::Delete));
    _usr_delete->Grow(std::make_unique<CTree>(CTree("-arg", USER::DeleteArg)));
    _user->Grow(std::move(_usr_delete));
    
    _root.Grow(std::move(_user));
    
    std::unique_ptr<CTree> _course = std::make_unique<CTree>(CTree("course", COURSE::Help));
    _course->Grow(std::make_unique<CTree>(CTree("help", COURSE::Help)));
    _course->Grow(std::make_unique<CTree>(CTree("view", COURSE::View)));
    
    std::unique_ptr<CTree> _crs_detail = std::make_unique<CTree>(CTree("detail", COURSE::Detail));
    _crs_detail->Grow(std::make_unique<CTree>(CTree("-arg", COURSE::DetailArg)));
    _course->Grow(std::move(_crs_detail));
    
    std::unique_ptr<CTree> _crs_create = std::make_unique<CTree>(CTree("create", COURSE::Create));
    _crs_create->Grow(std::make_unique<CTree>(CTree("-arg", COURSE::CreateArg)));
    _course->Grow(std::move(_crs_create));
    
    std::unique_ptr<CTree> _crs_delete = std::make_unique<CTree>(CTree("delete", COURSE::Delete));
    _crs_delete->Grow(std::make_unique<CTree>(CTree("-arg", COURSE::DeleteArg)));
    _course->Grow(std::move(_crs_delete));
    
    std::unique_ptr<CTree> _crs_assign = std::make_unique<CTree>(CTree("assign", COURSE::Assign));
    _crs_assign->Grow(std::make_unique<CTree>(CTree("-arg", COURSE::AssignArg)));
    _course->Grow(std::move(_crs_assign));
    
    std::unique_ptr<CTree> _crs_enroll = std::make_unique<CTree>(CTree("enroll", COURSE::Enroll));
    _crs_enroll->Grow(std::make_unique<CTree>(CTree("-arg", COURSE::EnrollArg)));
    _course->Grow(std::move(_crs_enroll));
    
    std::unique_ptr<CTree> _crs_remove = std::make_unique<CTree>(CTree("remove", COURSE::Remove));
    _crs_remove->Grow(std::make_unique<CTree>(CTree("-arg", COURSE::RemoveArg)));
    _course->Grow(std::move(_crs_remove));
    _root.Grow(std::move(_course));
    
    _root.Grow(std::make_unique<CTree>(CTree("help", Help)));
    _root.Grow(std::make_unique<CTree>(CTree("save", Save)));
    _root.Grow(std::make_unique<CTree>(CTree("script", Script)));
    _root.Grow(std::make_unique<CTree>(CTree("pswd", Pswd)));
    _root.Grow(std::make_unique<CTree>(CTree("logout", Logout)));
    _root.Grow(std::make_unique<CTree>(CTree("exit", Exit)));
}

// 无效命令。
void ADM::None()
{
    IO::ERROR("未知命令，输入 `help` 以获取更多信息。");
}

// 帮助信息。
void ADM::Help()
{
    IO::PRINT("可用命令：");
    IO::PRINT("  help    - 显示本帮助信息");
    IO::PRINT("  save    - 保存数据");
    IO::PRINT("  pswd    - 更改密码");
    IO::PRINT("  logout  - 退出当前用户");
    IO::PRINT("  exit    - 退出程序");
    IO::PRINT("  user    - 执行用户管理");
    IO::PRINT("  course  - 执行课程管理");
    IO::PRINT("脚本自动化：");
    IO::PRINT("  script        - 运行脚本文件");
    IO::PRINT("  script [path] - 在 [path] 处执行脚本文件");
}

// 保存数据。
void ADM::Save()
{
    IO::MESSG("保存数据。。。");
    DM::Save();
    IO::MESSG("数据已保存。");
}

// 脚本处理。
void ADM::Script()
{
    std::string path;
    VAR::remainArgs >> path;
    if (VS::IsWhiteString(path))
    {
        IO::INPUT("脚本路径") >> path;
    }
    
    std::fstream scriptFile(path, std::ios::in);
    if (!scriptFile.good())
    {
        IO::ERROR("脚本运行失败。");
        return;
    }
    
    std::string line;
    std::vector<std::string> cmd;
    std::function<void()> func;
    int pos;
    for (int i = 0; std::getline(scriptFile, line); i++)
    {
        IO::PRINT(i, "：", line);
        CTree::CommandSlice(line, cmd);
        func = VAR::admCmd.Retrieve(cmd, pos);
        
        VAR::remainArgs = std::stringstream();
        for (int i = pos; i < cmd.size(); i++)
        {
            VAR::remainArgs << cmd[i] << " ";
        }
        
        if (Execute(func) == false)
        {
            IO::ERROR("脚本中止：（", i, "） ", line);
            return;
        }
    }
}

// 修改密码。
void ADM::Pswd()
{
    std::string oldpswd = IO::SECRT("旧密码");
    
    if (VAR::currentUser.Authenticate(oldpswd) == false)
    {
        IO::ERROR("密码错误。");
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
    
    IO::MESSG("密码已更改。");
}

// 退出登录。
void ADM::Logout()
{
    if (IO::CHECK(false, "确认退出？") == false)
    {
        IO::MESSG("退出已取消");
        return;
    }
    IO::MESSG("成功退出，再见 ", VAR::currentUser.Name(), "。");
    VAR::currentUser = UNKOWN_USER;
}

// 退出程序。
void ADM::Exit()
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

// 用户管理帮助信息。
void ADM::USER::Help()
{
    IO::PRINT("可用命令：");
    IO::PRINT("  help    - 显示本帮助信息");
    IO::PRINT("  view    - 显示所有用户");
    IO::PRINT("  pswd    - 更改密码");
    IO::PRINT("  detail  - 显示用户细节");
    IO::PRINT("  create  - 创建用户");
    IO::PRINT("  delete  - 删除用户");
    IO::PRINT("额外参数：");
    IO::PRINT("  detail -arg [用户 ID]");
    IO::PRINT("  create -arg [用户类型 (stu/tch)] [用户 ID] [用户名]");
    IO::PRINT("  delete -arg [用户 ID]");
    IO::PRINT("示例：");
    IO::PRINT("  user view");
    IO::PRINT("  user detail -arg 20220001");
}

// 显示所有用户。
void ADM::USER::View()
{
    List<User> users = DM::AllUsers();
    for (int i = 0; i < users.Length(); i++)
    {
        IO::PRINT(ADM::USER::Peek(users[i].ID()));
    }
}

// 管理用户密码。
void ADM::USER::Pswd()
{
    std::string adminpswd = IO::SECRT("管理员密码");
    if (VAR::currentUser.Authenticate(adminpswd) == false)
    {
        IO::ERROR("密码错误。");
        return;
    }
    
    ID_t uid = -1;
    IO::INPUT("用户 ID") >> uid;
    
    if (!DM::HasUser(uid))
    {
        IO::ERROR("查询不到 ID ", uid, "的用户，运行失败。");
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
    
    User& user = DM::GetUser(uid);
    user.SetPassword(newpswd);
    IO::MESSG("密码已更改。");
}

// 显示用户详情。
void ADM::USER::Detail()
{
    ID_t uid = -1;
    IO::INPUT("用户 ID") >> uid;
    if (!DM::HasUser(uid))
    {
        IO::ERROR("查询不到 ID  ", uid, "的用户，运行失败。");
        return;
    }
    
    ADM::USER::Display(uid);
}

// 创建用户。
void ADM::USER::Create()
{
FLAG_FetchUserInfo:
    int type = -1;
    IO::INPUT("用户类型 (学生 1, 教师 2)") >> type;
    if (type != UserType::study && type != UserType::teach)
    {
        IO::ERROR("非法用户类型，运行失败。");
        return;
    }
    
    ID_t uid = 0;
    IO::INPUT("用户 ID") >> uid;
    
    if (DM::HasUser(uid))
    {
        IO::ERROR("ID为 ", uid, " 的用户已存在，运行失败。");
        return;
    }
    
    std::string name = IO::CLINE("用户名");
    
    IO::PRINT("用户 ID：", uid);
    switch (type)
    {
    case UserType::study: IO::PRINT("用户类型: 学生"); break;
    case UserType::teach: IO::PRINT("用户类型: 教师"); break;
    }
    IO::PRINT("用户名：", name);
    IO::PRINT("默认密码与ID相同");
    if (IO::CHECK(true, "已确认全部信息？") == false)
    {
        if (IO::CHECK(false, "重新输入信息？") == false)
        {
            IO::MESSG("本次运行失败。");
            return;
        }
        goto FLAG_FetchUserInfo;
    }
    
    switch (type)
    {
    case UserType::study:
        DM::AddStudent(Student(uid), name);
        break;
    case UserType::teach:
        DM::AddTeacher(Teacher(uid), name);
        break;
    }
    IO::MESSG("成功创建用户。");
}

// 删除用户。
void ADM::USER::Delete()
{
    ID_t uid = -1;
    IO::INPUT("用户 ID") >> uid;
    
    if (!DM::HasUser(uid))
    {
        IO::ERROR("查询不到 ID ", uid, "的用户，运行失败。");
        return;
    }
    
    UserType type = DM::GetUser(uid).Type();
    User user = DM::GetUser(uid);
    
    Display(uid);
    if (IO::CHECK(false, "确认删除用户？") == false)
    {
        IO::MESSG("删除已取消。");
        return;
    }
    
    switch (type)
    {
    case UserType::admin:
        IO::ERROR("不可删除管理员，运行失败。");
        return;
    case UserType::study: {
        DM::RemoveStudent(uid);
        break; }
    case UserType::teach: {
        DM::RemoveTeacher(uid);
        break; }
    }
}

// 显示用户详情。
// 【内部操作】该函数不应被构建入命令树。
void ADM::USER::Display(ID_t _uid)
{
    if (!DM::HasUser(_uid)) { return; }
    
    User user = DM::GetUser(_uid);
    IO::PRINT("用户 ID: ", user.ID());
    switch (user.Type())
    {
    case UserType::admin: IO::PRINT("用户类型：管理员"); break;
    case UserType::study: IO::PRINT("用户类型：学生"); break;
    case UserType::teach: IO::PRINT("用户类型：教师"); break;
    }
    IO::PRINT("用户名：", user.Name());
    switch (user.Type())
    {
    case UserType::study: {
        Student stu = DM::GetStudent(_uid);
        
        IO::PRINT("已选课程：");
        List<ID_t> selected = stu.Selected();
        for (int i = 0; i < selected.Length(); i++)
        {
            IO::PRINT("  - ", ADM::COURSE::Peek(selected[i]));
        }
        break; }
    case UserType::teach: {
        Teacher tch = DM::GetTeacher(_uid);
        
        IO::PRINT("教育课程：");
        List<ID_t> teaching = tch.Taught();
        for (int i = 0; i < teaching.Length(); i++)
        {
            IO::PRINT("  - ", ADM::COURSE::Peek(teaching[i]));
        }
        break; }
    }
}

// 获取用户信息。
// 【内部操作】该函数不应被构建入命令树。
std::string ADM::USER::Peek(ID_t _uid)
{
    if (!DM::HasUser(_uid)) { return ""; }
    
    User user = DM::GetUser(_uid);
    std::string info = "";
    switch (user.Type())
    {
    case UserType::admin: info += "[管理员] "; break;
    case UserType::study: info += "[学生] "; break;
    case UserType::teach: info += "[教师] "; break;
    }
    info += std::to_string(user.ID()) + " ";
    info += "\"" + user.Name() + "\"";
    
    return info;
}

// 显示用户详情。（从参数天桥中获取数据）
void ADM::USER::DetailArg()
{
    ID_t uid = -1;
    VAR::remainArgs >> uid;
    
    if (!DM::HasUser(uid))
    {
        IO::ERROR("查询不到 ID ", uid, "的用户，运行失败。");
        return;
    }
    
    Display(uid);
}

// 创建用户。（从参数天桥中获取数据）
void ADM::USER::CreateArg()
{
    std::string typestr = "";
    VAR::remainArgs >> typestr;
    if (typestr != "stu" && typestr != "tch" && typestr != "1" && typestr != "2")
    {
        IO::ERROR("非法用户类型，运行失败。");
        return;
    }
    
    UserType type;
    if (typestr == "stu" || typestr == "1") { type = UserType::study; }
    else if (typestr == "tch" || typestr == "2") { type = UserType::teach; }
    
    ID_t uid = 0;
    VAR::remainArgs >> uid;
    
    if (DM::HasUser(uid))
    {
        IO::ERROR("ID为 ", uid, " 的用户已存在，运行失败。");
        return;
    }
    
    std::string name = "";
    VAR::remainArgs >> name;
    std::string tmp = "";
    while (VAR::remainArgs >> tmp) { name += " " + tmp; }
    
    switch (type)
    {
    case UserType::study:
        DM::AddStudent(Student(uid), name);
        break;
    case UserType::teach:
        DM::AddTeacher(Teacher(uid), name);
        break;
    }
    IO::MESSG("成功创建用户。");
}

// 删除用户。（从参数天桥中获取数据）
void ADM::USER::DeleteArg()
{
    ID_t uid = -1;
    VAR::remainArgs >> uid;
    
    if (!DM::HasUser(uid))
    {
        IO::ERROR("查询不到 ID ", uid, "的用户，运行失败。");
        return;
    }
    
    UserType type = DM::GetUser(uid).Type();
    User user = DM::GetUser(uid);
    
    switch (type)
    {
    case UserType::admin:
        IO::ERROR("不可删除管理员，运行失败。");
        return;
    case UserType::study:
        DM::RemoveStudent(uid);
        break;
    case UserType::teach:
        DM::RemoveTeacher(uid);
        break;
    }
    IO::MESSG("用户删除成功");
}

// 课程管理帮助信息。
void ADM::COURSE::Help()
{
    IO::PRINT("可用命令：");
    IO::PRINT("  help    - 显示本帮助信息");
    IO::PRINT("  view    - 显示所有课程");
    IO::PRINT("  detail  - 显示课程细节");
    IO::PRINT("  create  - 创建课程");
    IO::PRINT("  delete  - 删除课程");
    IO::PRINT("  assign  - 为课程分配教师");
    IO::PRINT("  enroll  - 为学生注册课程");
    IO::PRINT("  remove  - 从课程中删除学生");
    IO::PRINT("额外参数：");
    IO::PRINT("  detail -arg [课程 ID]");
    IO::PRINT("  create -arg [课程 ID] [容量] [教师 ID] [name]");
    IO::PRINT("  delete -arg [课程 ID]");
    IO::PRINT("  assign -arg [课程 ID] [教师 ID]");
    IO::PRINT("  enroll -arg [课程 ID] [学生 ID]");
    IO::PRINT("  remove -arg [课程 ID] [学生 ID]");
    IO::PRINT("示例：");
    IO::PRINT("  course view");
    IO::PRINT("  course detail -arg 123");
}

// 查看所有课程。
void ADM::COURSE::View()
{
    List<Course> courses = DM::AllCourses();
    for (int i = 0; i < courses.Length(); i++)
    {
        IO::PRINT(ADM::COURSE::Peek(courses[i].ID()));
    }
}

// 显示课程详情。
void ADM::COURSE::Detail()
{
    ID_t cid = -1;
    IO::INPUT("课程 ID") >> cid;
    if (!DM::HasCourse(cid))
    {
        IO::ERROR("查询不到 ID ", cid, "的课程，运行失败。");
        return;
    }
    
    Course course = DM::GetCourse(cid);
    Display(cid);
}

// 创建课程。
void ADM::COURSE::Create()
{
FLAG_FetchCourseInfo:
    ID_t cid = 0;
    IO::INPUT("课程 ID") >> cid;
    
    if (DM::HasCourse(cid))
    {
        IO::ERROR("ID为 ", cid, " 的课程已存在，运行失败。");
        return;
    }
    
    std::string name = IO::CLINE("课程名称");
    Size_t capacity = 0;
    IO::INPUT("课程容量") >> capacity;
    ID_t teacher = -1;
    IO::INPUT("课任教师 ID") >> teacher;
    
    if (!DM::HasTeacher(teacher))
    {
        IO::ERROR("查询不到 ID ", teacher, "的教师，运行失败。");
        return;
    }
    
    IO::PRINT("课程 ID：", cid);
    IO::PRINT("课程名称：", name);
    IO::PRINT("课程容量：", capacity);
    IO::PRINT("课任教师：", teacher);
    if (IO::CHECK(true, "已确认全部信息？") == false)
    {
        if (IO::CHECK(false, "重新输入信息？") == false)
        {
            IO::MESSG("本次运行失败。");
            return;
        }
        goto FLAG_FetchCourseInfo;
    }
    
    DM::AddCourse(Course(cid, name, capacity, teacher));
}

// 删除课程。
void ADM::COURSE::Delete()
{
    ID_t cid = -1;
    IO::INPUT("课程 ID") >> cid;
    
    if (!DM::HasCourse(cid))
    {
        IO::ERROR("查询不到 ID ", cid, "的课程，运行失败。");
        return;
    }
    
    Course course = DM::GetCourse(cid);
    
    Display(cid);
    if (IO::CHECK(false, "确认删除课程？") == false)
    {
        IO::MESSG("删除已取消。");
        return;
    }
    
    DM::RemoveCourse(cid);
    IO::MESSG("课程删除成功。");
}

// 为老师分配课程。
void ADM::COURSE::Assign()
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
    
    ID_t teacher = -1;
    IO::INPUT("课任教师 ID") >> teacher;
    
    if (!DM::HasTeacher(teacher))
    {
        IO::ERROR("查询不到 ID ", teacher, "的教师，运行失败。");
        return;
    }
    
    ADM::USER::Display(teacher);
    
    if (IO::CHECK(true, "确认分配？") == false)
    {
        IO::MESSG("分配已取消。");
        return;
    }
    
    DM::Assign(teacher, cid);
    IO::MESSG("分配成功。");
}

// 为学生选择课程。
void ADM::COURSE::Enroll()
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
    
    ID_t uid = -1;
    IO::INPUT("学生 ID") >> uid;
    
    if (!DM::HasStudent(uid))
    {
        IO::ERROR("查询不到 ID ", uid, "的学生，运行失败。");
        return;
    }
    
    ADM::USER::Display(uid);
    
    if (IO::CHECK(true, "确认选课？") == false)
    {
        IO::MESSG("选课已取消。");
        return;
    }
    
    DM::Enroll(uid, cid);
    IO::MESSG("选课成功。");
}

// 为学生退选课程。
void ADM::COURSE::Remove()
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
    
    ID_t uid = -1;
    IO::INPUT("学生 ID") >> uid;
    
    if (!DM::HasStudent(uid))
    {
        IO::ERROR("查询不到 ID ", uid, "的学生，运行失败。");
        return;
    }
    
    ADM::USER::Display(uid);
    
    if (IO::CHECK(true, "确认退课？") == false)
    {
        IO::MESSG("退课已取消。");
        return;
    }
    
    DM::Remove(uid, cid);
    IO::MESSG("退课成功。");
}

// 显示课程详情。
// 【内部操作】该函数不应被构建入命令树。
void ADM::COURSE::Display(ID_t _cid)
{
    if (!DM::HasCourse(_cid)) { return; }
    
    Course course = DM::GetCourse(_cid);
    IO::PRINT("课程 ID: ", course.ID());
    IO::PRINT("课程名：", course.Name());
    IO::PRINT("课程容量：", course.Capacity());
    IO::PRINT("已选课学生数量", course.Enrolled().Length());
    IO::PRINT("课任教师：", DM::GetUser(course.Teacher()).Name(), " ", course.Teacher());
}

// 获取课程信息。
// 【内部操作】该函数不应被构建入命令树。
std::string ADM::COURSE::Peek(ID_t _cid)
{
    if (!DM::HasCourse(_cid)) { return ""; }
    
    Course course = DM::GetCourse(_cid);
    std::string info = "";
    info += std::to_string(course.ID()) + " ";
    info += "\"" + course.Name() + "\"";
    info += " (" + std::to_string(course.Enrolled().Length()) + "/" + std::to_string(course.Capacity()) + ") ";
    info += DM::GetUser(course.Teacher()).Name();
    
    return info;
}

// 显示课程详情。（从参数天桥中获取数据）
void ADM::COURSE::DetailArg()
{
    ID_t cid = -1;
    VAR::remainArgs >> cid;
    
    if (!DM::HasCourse(cid))
    {
        IO::ERROR("查询不到 ID ", cid, "的课程，运行失败。");
        return;
    }
    
    ADM::COURSE::Display(cid);
}

// 创建课程。（从参数天桥中获取数据）
void ADM::COURSE::CreateArg()
{
    ID_t cid = 0;
    VAR::remainArgs >> cid;
    
    if (DM::HasCourse(cid))
    {
        IO::ERROR("ID为 ", cid, " 的课程已存在，运行失败。");
        return;
    }
    
    Size_t capacity = 0;
    VAR::remainArgs >> capacity;
    ID_t teacher = -1;
    VAR::remainArgs >> teacher;
    
    if (!DM::HasTeacher(teacher))
    {
        IO::ERROR("查询不到 ID ", teacher, "的教师，运行失败。");
        return;
    }
    
    std::string name = "";
    VAR::remainArgs >> name;
    std::string tmp = "";
    while (VAR::remainArgs >> tmp) { name += " " + tmp; }
    
    DM::AddCourse(Course(cid, name, capacity, teacher));
    IO::MESSG("课程创建成功。");
}

// 删除课程。（从参数天桥中获取数据）
void ADM::COURSE::DeleteArg()
{
    ID_t cid = -1;
    VAR::remainArgs >> cid;
    
    if (!DM::HasCourse(cid))
    {
        IO::ERROR("查询不到 ID ", cid, "的课程，运行失败。");
        return;
    }
    
    DM::RemoveCourse(cid);
    IO::MESSG("课程删除成功。");
}

// 为老师分配课程。（从参数天桥中获取数据）
void ADM::COURSE::AssignArg()
{
    ID_t cid = -1;
    VAR::remainArgs >> cid;
    
    if (!DM::HasCourse(cid))
    {
        IO::ERROR("查询不到 ID ", cid, "的课程，运行失败。");
        return;
    }
    
    ID_t teacher = -1;
    VAR::remainArgs >> teacher;
    
    if (!DM::HasTeacher(teacher))
    {
        IO::ERROR("查询不到 ID ", teacher, "的教师，运行失败。");
        return;
    }
    
    DM::Assign(teacher, cid);
    IO::MESSG("分配成功。");
}

// 为学生选择课程。（从参数天桥中获取数据）
void ADM::COURSE::EnrollArg()
{
    ID_t cid = -1;
    VAR::remainArgs >> cid;
    
    if (!DM::HasCourse(cid))
    {
        IO::ERROR("查询不到 ID ", cid, "的课程，运行失败。");
        return;
    }
    
    ID_t uid = -1;
    VAR::remainArgs >> uid;
    
    if (!DM::HasStudent(uid))
    {
        IO::ERROR("查询不到 ID ", uid, "的学生，运行失败。");
        return;
    }
    
    DM::Enroll(uid, cid);
    IO::MESSG("选课成功。");
}

// 为学生退选课程。（从参数天桥中获取数据）
void ADM::COURSE::RemoveArg()
{
    ID_t cid = -1;
    VAR::remainArgs >> cid;
    
    if (!DM::HasCourse(cid))
    {
        IO::ERROR("查询不到 ID ", cid, "的课程，运行失败。");
        return;
    }
    
    ID_t uid = -1;
    VAR::remainArgs >> uid;
    
    if (!DM::HasStudent(uid))
    {
        IO::ERROR("查询不到 ID ", uid, "的学生，运行失败。");
        return;
    }
    
    DM::Remove(uid, cid);
    IO::MESSG("退课成功。");
}

#endif

/*

adminis
├── help
├── save
├── user
│   ├── help
│   ├── view
│   ├── detail
│   ├── create
│   ├── delete
├── course
│   ├── help
│   ├── view
│   ├── detail
│   ├── create
│   ├── delete
│   ├── assign
│   └── enroll
├── logout
└── exit


*/