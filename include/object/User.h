#ifndef USER_H
#define USER_H

#include "../utility/LynType.h"

#include "../struct/List.h"

#include <string>

namespace ADM
{
    namespace USER
    {
        void Pswd();
    }
}

enum UserType
{
    empty = -1,
    admin = 0,
    study = 1,
    teach = 2
};

class User
{
    friend class DM;
    friend void ADM::USER::Pswd();
private:
    ID_t id;
    UserType type;
    std::string name;
    std::string pswd;
public:
    User(UserType _type, ID_t _id, std::string _name, std::string _pswd);
    
    ID_t ID() const;
    UserType Type();
    std::string Name();
    bool Authenticate(std::string _pswd);
    bool ChangePassword(std::string _oldpswd, std::string _newpswd);
    
    bool operator == (ID_t _id);
private:
    void SetPassword(std::string _pswd);
};

// == ���� == //

// δ֪�û�����ʾδ��¼��
const User UNKOWN_USER(UserType::empty, -1, "δ��¼", SSP::Encrypt(""));

// == ʵ�� == //

User::User(UserType _type, ID_t _id, std::string _name, std::string _pswd)
{
    id = _id;
    type = _type;
    name = _name;
    pswd = _pswd;
}

// �����û� ID��
ID_t User::ID() const
{
    return id;
}

// �����û����͡�
UserType User::Type()
{
    return type;
}

// �����û�������
std::string User::Name()
{
    return name;
}

// ��֤�����Ƿ���ȷ��
bool User::Authenticate(std::string _pswd)
{
    return pswd == _pswd;
}

// �޸����롣
bool User::ChangePassword(std::string _oldpswd, std::string _newpswd)
{
    if (Authenticate(_oldpswd))
    {
        pswd = _newpswd;
        return true;
    }
    return false;
}

// �������롣
// �������������ú���Ϊ�������������
void User::SetPassword(std::string _pswd)
{
    pswd = _pswd;
}

// ��������жϣ��ȶ��û� ID��
bool User::operator == (ID_t _id)
{
    return id == _id;
}

#endif