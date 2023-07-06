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

// ��Ч���
void TCH::None()
{
    IO::ERROR("δ֪������� `help` �Ի�ȡ������Ϣ��");
}

// ������������
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

// ������Ϣ��
void TCH::Help()
{
    IO::PRINT("�������");
    IO::PRINT("  �γ̹���");
    IO::PRINT("    mine    - ��ʾ�ҵĿγ�");
    IO::PRINT("    view    - ��ʾ���пγ�");
    IO::PRINT("    detail  - ��ʾ�γ�ϸ��");
    IO::PRINT("    create  - �����γ�");
    IO::PRINT("    delete  - ɾ���γ�");
    IO::PRINT("  �������");
    IO::PRINT("    help    - ��ʾ��������Ϣ");
    IO::PRINT("    pswd    - ��������");
    IO::PRINT("    logout  - �ǳ���ǰ�û�");
    IO::PRINT("    exit    - �˳�����");
}

// �鿴�ҵĿγ̡�
void TCH::Mine()
{
    Teacher me = DM::GetTeacher(VAR::currentUser.ID());
    List<ID_t> teaching = me.Taught();
    
    IO::PRINT("�ҵĿγ̣�");
    for (int i = 0; i < teaching.Length(); i++)
    {
        IO::PRINT(ADM::COURSE::Peek(teaching[i]));
    }
}

// �鿴���пγ̡�
void TCH::View()
{
    List<Course> courses = DM::AllCourses();
    IO::PRINT("���пγ�");
    for (int i = 0; i < courses.Length(); i++)
    {
        IO::PRINT("  - ", ADM::COURSE::Peek(courses[i].ID()));
    }
}

// �鿴�γ����顣
void TCH::Detail()
{
    ID_t cid = -1;
    IO::INPUT("�γ� ID") >> cid;
    if (!DM::HasCourse(cid))
    {
         IO::ERROR("��ѯ���� ID ", cid, "�Ŀγ̣�����ʧ�ܡ�");
        return;
    }
    
    Course course = DM::GetCourse(cid);
    ADM::COURSE::Display(cid);
}

// �����γ̡�
void TCH::Create()
{
FLAG_FetchCourseInfo:
    ID_t cid = -1;
    IO::INPUT("�γ� ID") >> cid;
    
    if (DM::HasCourse(cid))
    {
        IO::ERROR("ID ", cid, "�Ŀγ��Ѵ��ڣ�����ʧ�ܡ�");
        return;
    }
    
    std::string name = IO::CLINE("�γ�����");
    Size_t capacity = 0;
    IO::INPUT("�γ�����") >> capacity;
    
    IO::PRINT("�γ� ID��", cid);
    IO::PRINT("�γ����ƣ�", name);
    IO::PRINT("�γ�������", capacity);
    if (IO::CHECK(true, "��ȫ��ȷ�ϣ�") == false)
    {
        if (IO::CHECK(false, "����������Ϣ��") == false)
        {
            IO::MESSG("��������ʧ�ܡ�");
            return;
        }
        goto FLAG_FetchCourseInfo;
    }
    
    DM::AddCourse(Course(cid, name, capacity, VAR::currentUser.ID()));
    IO::MESSG("�γ��Ѵ�����");
}

// ɾ���γ̡�
void TCH::Delete()
{
    ID_t cid = -1;
    IO::INPUT("�γ� ID") >> cid;
    
    Course course = DM::GetCourse(cid);
    
    if (course.Teacher() != VAR::currentUser.ID())
    {
        IO::ERROR("�����Ǹÿγ̵Ŀ��ν�ʦ������ʧ�ܡ�");
        return;
    }
    
    if (IO::CHECK(false, "ȷ��ɾ����") == false)
    {
        IO::MESSG("ɾ����ȡ����");
        return;
    }
    
    DM::RemoveCourse(cid);
    IO::MESSG("�γ���ɾ����");
}

// �޸����롣
void TCH::Pswd()
{
    std::string oldpswd = IO::SECRT("������");
    
    if (VAR::currentUser.Authenticate(oldpswd) == false)
    {
        IO::ERROR("�������");
        return;
    }
    
    std::string newpswd = IO::SECRT("������");
    std::string cfmpswd = IO::SECRT("ȷ������");
    
    if (newpswd != cfmpswd)
    {
        IO::ERROR("���벻ƥ�䡣");
        return;
    }
    
    if (newpswd == SSP::Encrypt(""))
    {
        IO::MESSG("����δ�ı䡣");
        return;
    }
    
    User& user = DM::GetUser(VAR::currentUser.ID());
    user.ChangePassword(oldpswd, newpswd);
    VAR::currentUser = user;
    
    IO::MESSG("�����Ѹı䡣");
}

// �˳���¼��
void TCH::Logout()
{
    if (IO::CHECK(false, "ȷ�ϵǳ���") == false)
    {
        IO::MESSG("�ǳ���ȡ��");
        return;
    }
    IO::MESSG("�ɹ��ǳ����ټ� ", VAR::currentUser.Name(), "��");
    VAR::currentUser = UNKOWN_USER;
}

// �˳�����
void TCH::Exit()
{
    if (IO::CHECK(false, "ȷ���˳�����") == false)
    {
        IO::MESSG("�˳���ȡ��");
        return;
    }
    if (IO::CHECK(false, "�ٴ�ȷ�ϣ��˳�����") == false)
    {
        IO::MESSG("�˳���ȡ��");
        return;
    }
    IO::MESSG("������ֹ������");
    VAR::isRunning = false;
}

#endif