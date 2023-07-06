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

// ������������
void CMD::Construct(CTree& _root)
{
    _root.Grow(std::make_unique<CTree>(CTree("help", Help)));
    _root.Grow(std::make_unique<CTree>(CTree("info", Info)));
    _root.Grow(std::make_unique<CTree>(CTree("color", Color)));
    _root.Grow(std::make_unique<CTree>(CTree("login", Login)));
    _root.Grow(std::make_unique<CTree>(CTree("exit", Exit)));
}

// δ֪���
void CMD::None()
{
    IO::ERROR("δ֪������� `help` �Ի�ȡ������Ϣ��");
}

// ������Ϣ��
void CMD::Help()
{
    IO::PRINT("�������");
    IO::PRINT("  help   - ��ʾ��������Ϣ");
    IO::PRINT("  info   - ��ʾ������Ϣ");
    IO::PRINT("  color  - �����ɫ����");
    IO::PRINT("  login  - ��¼�˻�");
    IO::PRINT("  exit   - �˳�����");
}

// ������Ϣ��
void CMD::Info()
{
    IO::PRINT(" ___________");
    IO::PRINT("|           |   ��������: Catalog");
    IO::PRINT("|  catalog  |   �汾: 1.0.3");
    IO::PRINT("| __        |   ��Ϣ: C �������");
    IO::PRINT(" /  /_______|   ����: ѡ�ι���ϵͳ");
    IO::PRINT(" \\__________|   �㷨: �����ļ�����");
    IO::PRINT("");
}

// �л���ɫģʽ��
void CMD::Color()
{
    bool colored = IO::FlipColorStatus();
    IO::MESSG("��ɫ���� ", colored ? "����" : "δ����", "��");
}

// ��¼��
void CMD::Login()
{
    ID_t uid = -1;
    std::string input;
    IO::INPUT("�û� ID") >> input;
    if (VS::IsNumber(input)) { uid = std::stoll(input); }
    
    if (!DM::HasUser(uid))
    {
        IO::ERROR("��ѯ���� ID ", uid, "���û�������ʧ�ܡ�");
        return;
    }
    
    User& user = DM::GetUser(uid);
    
    std::string pswd;
    for (int attempt = 0; attempt < 3; attempt++)
    {
        pswd = IO::SECRT("����");
        if (user.Authenticate(pswd))
        {
            IO::MESSG("��½�ɹ�����ӭ ", user.Name(), "��");
            VAR::currentUser = user;
            return;
        }
        else
        {
            IO::ALERT("�������,ʣ�� ", 2 - attempt, " �γ��Ի���");
        }
    }
    IO::ERROR("�ѳ���3�Σ�������󣬲�����ֹ��");
}

// �˳�����
void CMD::Exit()
{
    if (IO::CHECK(false, "��ȷ���˳������룿") == false)
    {
        IO::MESSG("�˳���ȡ��");
        return;
    }
    IO::MESSG("������ֹ������");
    VAR::isRunning = false;
}

#endif