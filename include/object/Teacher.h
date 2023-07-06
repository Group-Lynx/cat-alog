#ifndef TEACHER_H
#define TEACHER_H

#include "../struct/List.h"

class Teacher
{
    friend class DM;
private:
    ID_t id;
    List<ID_t> taught;
private:
    void Attach(ID_t _courseId);
    void Detach(ID_t _courseId);
public:
    Teacher(ID_t _id);
    
    ID_t ID() const;
    List<ID_t> Taught() const;
    bool AlreadyTaught(ID_t _courseId);
    bool IsFree();
    
    bool operator == (ID_t _id);
};

// == 实现 == //

// 将指定课程的课号添加至已教课程。
// 【无视非法】该函数不进行合法性验证，使用者需保证合法。
// 【本地异步】该函数仅对本类进行修改，不会同步修改它处。
void Teacher::Attach(ID_t _courseId)
{
    taught.Append(_courseId);
}

// 将指定课程的课号从已教课程中移除。
// 【无视非法】该函数不进行合法性验证，使用者需保证合法。
// 【本地异步】该函数仅对本类进行修改，不会同步修改它处。
void Teacher::Detach(ID_t _courseId)
{
    taught.Remove(_courseId);
}

Teacher::Teacher(ID_t _id)
{
    id = _id;
}

// 获取教师 ID。
ID_t Teacher::ID() const
{
    return id;
}

// 获取已教课程。
List<ID_t> Teacher::Taught() const
{
    return taught;
}

// 判断老师是否教授指定课程。
bool Teacher::AlreadyTaught(ID_t _courseId)
{
    return taught.Search(_courseId).has_value();
}

// 判断是否已经教课。
bool Teacher::IsFree()
{
    return taught.Length() == 0;
}

// 重载相等判断，比对教师 ID。
bool Teacher::operator == (ID_t _id)
{
    return id == _id;
}

#endif