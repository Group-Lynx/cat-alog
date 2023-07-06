#include "../include/command/CommandAdmin.h"
#include "../include/command/CommandStudent.h"
#include "../include/command/CommandTeacher.h"
#include "../include/command/CommandGeneral.h"

#include "../include/utility/ValidString.h"

#include "../include/data/GlobalVariable.h"

// 出厂设置
void FactoryReset()
{
    // 添加管理员账户。
    DM::AddUser(User(UserType::admin, 0, "管理员", SSP::Encrypt("admin")));
    // 显示程序信息。
    CMD::Info();
}

// 初始化程序。
void Initialize()
{
    // 若加载数据失败，则执行首次运行初始化。
    try
    {
        if (!DM::Load())
        {
            IO::MESSG("首次运行，初始化。。。");
            FactoryReset();
            IO::MESSG("初始化成功。");
        }
    }
    catch (const std::exception& excep)
    {
        IO::ERROR(excep.what());
        IO::ERROR("数据读取失败, 程序初始化。。。");
        FactoryReset();
    }
    
    // 构建各命令树。
    STU::Construct(VAR::stuCmd);
    TCH::Construct(VAR::tchCmd);
    ADM::Construct(VAR::admCmd);
    CMD::Construct(VAR::gnlCmd);
    
    // 初始化当前用户。
    VAR::currentUser = UNKOWN_USER;
}

// 执行函数，处理错误。
bool Execute(std::function<void()> _func)
{
    try { _func(); return true; }
    catch (const UnknownStudent& excep) { IO::ERROR("未查询到指定ID的学生。"); }
    catch (const UnknownCourse& excep) { IO::ERROR("未查询到指定ID的课程。"); }
    catch (const UnknownTeacher& excep) { IO::ERROR("未查询到指定ID的教师。"); }
    catch (const UnknownUser& excep) { IO::ERROR("未查询到指定ID的用户。"); }
    catch (const IDExists& excep) { IO::ERROR("ID已被占用。"); }
    catch (const AlreadyTaken& excep) { IO::ERROR("该学生已经选择这门课程。");}
    catch (const AlreadyTaught& excep) { IO::ERROR("该教师已经教授这门课程。"); }
    catch (const NotTaken& excep) { IO::ERROR("该学生并未选择这门课程。"); }
    catch (const NotTaught& excep) { IO::ERROR("该教师并未教授这门课程。"); }
    catch (const CourseIsFull& excep) { IO::ERROR("该课程已满。"); }
    catch (const CourseNotFree& excep) { IO::ERROR("该课程已有学生。"); }
    catch (const StudentNotFree& excep) { IO::ERROR("该学生已有选课。"); }
    catch (const TeacherNotFree& excep) { IO::ERROR("该教师已有授课。"); }
    catch (const std::exception& excep) { IO::ERROR(excep.what()); }
    return false;
}

// 终止程序。
void Finalize()
{
    DM::Save();
    IO::MESSG("程序正常中止。");
}

// 按间隔保存数据。
void ClockSave()
{
    static int count = 0;
    static const int interval = 0;
    
    if (count == interval)
    {
        DM::Save();
    }
    count = ((count == interval) ? 0 : count + 1);
}

int main()
{   
    Initialize();
    
    std::string input;
    std::vector<std::string> cmd;
    std::function<void()> func;
    int pos;
    
    while (VAR::isRunning)
    {
        // 显示用户信息，获取用户命令。
        input = IO::SHELL(VAR::currentUser.Name());
        if (VS::IsWhiteString(input)) { continue; }
        input = VS::Trim(input);
        
        // 解释用户命令。
        CTree::CommandSlice(input, cmd);
        switch(VAR::currentUser.Type())
        {
        case UserType::empty: func = VAR::gnlCmd.Retrieve(cmd, pos); break;
        case UserType::admin: func = VAR::admCmd.Retrieve(cmd, pos); break;
        case UserType::study: func = VAR::stuCmd.Retrieve(cmd, pos); break;
        case UserType::teach: func = VAR::tchCmd.Retrieve(cmd, pos); break;
        }
        
        // 传递剩余参数。
        VAR::remainArgs = std::stringstream();
        for (int i = pos; i < cmd.size(); i++)
        {
            VAR::remainArgs << cmd[i] << " ";
        }
        
        // 执行指令，处理错误。
        Execute(func);
        
        // 保存数据。
        ClockSave();
    }
    
    Finalize();
    
    return 0;
}