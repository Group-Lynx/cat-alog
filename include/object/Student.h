#ifndef STUDENT_H
#define STUDENT_H

#include "../struct/List.h"

class Student
{
    friend class DM;
private:
    ID_t id;
    List<ID_t> selected;
private:
    void Take(ID_t _courseId);
    void Drop(ID_t _courseId);
public:
    Student(ID_t _id);
    
    ID_t ID() const;
    List<ID_t> Selected() const;
    bool AlreadyTaken(ID_t _courseId);
    bool IsFree();
    
    bool operator == (ID_t _id);
};

// == 实现 == //

// 将指定课程的课号添加至已选课程。
// 【无视非法】该函数不进行合法性验证，使用者需保证合法。
// 【本地异步】该函数仅对本类进行修改，不会同步修改它处。
void Student::Take(ID_t _courseId)
{
    selected.Append(_courseId);
}

// 将指定课程的课号从已选课程中移除。
// 【无视非法】该函数不进行合法性验证，使用者需保证合法。
// 【本地异步】该函数仅对本类进行修改，不会同步修改它处。
void Student::Drop(ID_t _courseId)
{
    selected.Remove(_courseId);
}

Student::Student(ID_t _id)
{
    id = _id;
}

// 获取学生 ID。
ID_t Student::ID() const
{
    return id;
}

// 获取已选课程。
List<ID_t> Student::Selected() const
{
    return selected;
}

// 判断是否已经注册过指定课程。
bool Student::AlreadyTaken(ID_t _courseId)
{
    return selected.Search(_courseId).has_value();
}

// 判断是否已经选课。
bool Student::IsFree()
{
    return selected.Length() == 0;
}

// 重载相等判断，比对学生 ID。
bool Student::operator == (ID_t _id)
{
    return id == _id;
}

#endif