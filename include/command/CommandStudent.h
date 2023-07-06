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

// ��Ч���
void STU::None()
{
    IO::ERROR("δ֪������� `help` �Ի�ȡ������Ϣ��");
}

// ������������
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

// ������Ϣ��
void STU::Help()
{
    IO::PRINT("�������");
    IO::PRINT("  �γ̹���");
    IO::PRINT("    mine    - ��ʾ�ҵĿγ�");
    IO::PRINT("    view    - ��ʾ���пγ�");
    IO::PRINT("    detail  - ��ʾ�γ�ϸ��");
    IO::PRINT("    take    - ѡ��");
    IO::PRINT("    drop    - �˿�");
    IO::PRINT("  �������");
    IO::PRINT("    help    - ��ʾ��������Ϣ");
    IO::PRINT("    pswd    - ��������");
    IO::PRINT("    logout  - �ǳ���ǰ�û�");
    IO::PRINT("    exit    - �˳�����");
}

// �鿴�ҵĿγ̡�
void STU::Mine()
{
    Student me = DM::GetStudent(VAR::currentUser.ID());
    List<ID_t> selected = me.Selected();
    
    IO::PRINT("ѡ��γ̣�");
    for (int i = 0; i < selected.Length(); i++)
    {
        IO::PRINT("  - ", ADM::COURSE::Peek(selected[i]));
    }
}

// �鿴���пγ̡�
void STU::View()
{
    List<Course> courses = DM::AllCourses();
    IO::PRINT("���пγ̣�");
    for (int i = 0; i < courses.Length(); i++)
    {
        IO::PRINT("  - ", ADM::COURSE::Peek(courses[i].ID()));
    }
}

// �鿴�γ����顣
void STU::Detail()
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

// ѡ�Ρ�
void STU::Take()
{
    ID_t cid = -1;
    IO::INPUT("�γ� ID") >> cid;
    
    if (!DM::HasCourse(cid))
    {
        IO::ERROR("��ѯ���� ID ", cid, "�Ŀγ̣�����ʧ�ܡ�");
        return;
    }
    
    ADM::COURSE::Display(cid);
    
    Course course = DM::GetCourse(cid);
    if (course.IsFull())
    {
        IO::ERROR("�γ�����������ʧ�ܡ�");
        return;
    }
    
    if (IO::CHECK(true, "ȷ��ѡ�Σ�") == false)
    {
        IO::MESSG("ѡ����ȡ����");
        return;
    }
    
    DM::Enroll(VAR::currentUser.ID(), cid);
    IO::MESSG("ѡ�γɹ���");
}

// �˿Ρ�
void STU::Drop()
{
    ID_t cid = -1;
    IO::INPUT("�γ� ID") >> cid;
    
    if (!DM::HasCourse(cid))
    {
        IO::ERROR("��ѯ���� ID ", cid, "�Ŀγ̣�����ʧ�ܡ�");
        return;
    }
    
    ADM::COURSE::Display(cid);
    
    Course course = DM::GetCourse(cid);
    
    if (IO::CHECK(false, "ȷ���˿Σ�") == false)
    {
        IO::MESSG("�˿���ȡ��");
        return;
    }
    
    DM::Remove(VAR::currentUser.ID(), cid);
    IO::MESSG("�˿γɹ���");
}

// �޸����롣
void STU::Pswd()
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
void STU::Logout()
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
void STU::Exit()
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