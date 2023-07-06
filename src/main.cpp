#include "../include/command/CommandAdmin.h"
#include "../include/command/CommandStudent.h"
#include "../include/command/CommandTeacher.h"
#include "../include/command/CommandGeneral.h"

#include "../include/utility/ValidString.h"

#include "../include/data/GlobalVariable.h"

// ��������
void FactoryReset()
{
    // ��ӹ���Ա�˻���
    DM::AddUser(User(UserType::admin, 0, "����Ա", SSP::Encrypt("admin")));
    // ��ʾ������Ϣ��
    CMD::Info();
}

// ��ʼ������
void Initialize()
{
    // ����������ʧ�ܣ���ִ���״����г�ʼ����
    try
    {
        if (!DM::Load())
        {
            IO::MESSG("�״����У���ʼ��������");
            FactoryReset();
            IO::MESSG("��ʼ���ɹ���");
        }
    }
    catch (const std::exception& excep)
    {
        IO::ERROR(excep.what());
        IO::ERROR("���ݶ�ȡʧ��, �����ʼ��������");
        FactoryReset();
    }
    
    // ��������������
    STU::Construct(VAR::stuCmd);
    TCH::Construct(VAR::tchCmd);
    ADM::Construct(VAR::admCmd);
    CMD::Construct(VAR::gnlCmd);
    
    // ��ʼ����ǰ�û���
    VAR::currentUser = UNKOWN_USER;
}

// ִ�к������������
bool Execute(std::function<void()> _func)
{
    try { _func(); return true; }
    catch (const UnknownStudent& excep) { IO::ERROR("δ��ѯ��ָ��ID��ѧ����"); }
    catch (const UnknownCourse& excep) { IO::ERROR("δ��ѯ��ָ��ID�Ŀγ̡�"); }
    catch (const UnknownTeacher& excep) { IO::ERROR("δ��ѯ��ָ��ID�Ľ�ʦ��"); }
    catch (const UnknownUser& excep) { IO::ERROR("δ��ѯ��ָ��ID���û���"); }
    catch (const IDExists& excep) { IO::ERROR("ID�ѱ�ռ�á�"); }
    catch (const AlreadyTaken& excep) { IO::ERROR("��ѧ���Ѿ�ѡ�����ſγ̡�");}
    catch (const AlreadyTaught& excep) { IO::ERROR("�ý�ʦ�Ѿ��������ſγ̡�"); }
    catch (const NotTaken& excep) { IO::ERROR("��ѧ����δѡ�����ſγ̡�"); }
    catch (const NotTaught& excep) { IO::ERROR("�ý�ʦ��δ�������ſγ̡�"); }
    catch (const CourseIsFull& excep) { IO::ERROR("�ÿγ�������"); }
    catch (const CourseNotFree& excep) { IO::ERROR("�ÿγ�����ѧ����"); }
    catch (const StudentNotFree& excep) { IO::ERROR("��ѧ������ѡ�Ρ�"); }
    catch (const TeacherNotFree& excep) { IO::ERROR("�ý�ʦ�����ڿΡ�"); }
    catch (const std::exception& excep) { IO::ERROR(excep.what()); }
    return false;
}

// ��ֹ����
void Finalize()
{
    DM::Save();
    IO::MESSG("����������ֹ��");
}

// ������������ݡ�
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
        // ��ʾ�û���Ϣ����ȡ�û����
        input = IO::SHELL(VAR::currentUser.Name());
        if (VS::IsWhiteString(input)) { continue; }
        input = VS::Trim(input);
        
        // �����û����
        CTree::CommandSlice(input, cmd);
        switch(VAR::currentUser.Type())
        {
        case UserType::empty: func = VAR::gnlCmd.Retrieve(cmd, pos); break;
        case UserType::admin: func = VAR::admCmd.Retrieve(cmd, pos); break;
        case UserType::study: func = VAR::stuCmd.Retrieve(cmd, pos); break;
        case UserType::teach: func = VAR::tchCmd.Retrieve(cmd, pos); break;
        }
        
        // ����ʣ�������
        VAR::remainArgs = std::stringstream();
        for (int i = pos; i < cmd.size(); i++)
        {
            VAR::remainArgs << cmd[i] << " ";
        }
        
        // ִ��ָ��������
        Execute(func);
        
        // �������ݡ�
        ClockSave();
    }
    
    Finalize();
    
    return 0;
}