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

// == 常量 == //

// 未知用户，表示未登录。
const User UNKOWN_USER(UserType::empty, -1, "未登录", SSP::Encrypt(""));

// == 实现 == //

User::User(UserType _type, ID_t _id, std::string _name, std::string _pswd)
{
    id = _id;
    type = _type;
    name = _name;
    pswd = _pswd;
}

// 返回用户 ID。
ID_t User::ID() const
{
    return id;
}

// 返回用户类型。
UserType User::Type()
{
    return type;
}

// 返回用户姓名。
std::string User::Name()
{
    return name;
}

// 验证密码是否正确。
bool User::Authenticate(std::string _pswd)
{
    return pswd == _pswd;
}

// 修改密码。
bool User::ChangePassword(std::string _oldpswd, std::string _newpswd)
{
    if (Authenticate(_oldpswd))
    {
        pswd = _newpswd;
        return true;
    }
    return false;
}

// 设置密码。
// 【保留操作】该函数为特殊操作保留。
void User::SetPassword(std::string _pswd)
{
    pswd = _pswd;
}

// 重载相等判断，比对用户 ID。
bool User::operator == (ID_t _id)
{
    return id == _id;
}

#endif