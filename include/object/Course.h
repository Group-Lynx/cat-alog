#ifndef COURSE_H
#define COURSE_H

#include "../struct/List.h"

class Course
{
    friend class DM;
private:
    ID_t id;
    std::string name;
    Size_t capacity;
    ID_t teacher;
    List<ID_t> enrolled;
private:
    void Enroll(ID_t _studentId);
    void Remove(ID_t _studentId);
    void Assign(ID_t _teacherId);
public:
    Course(ID_t _id, std::string _name, Size_t _capacity, ID_t _teacher);
    
    ID_t ID() const;
    std::string Name() const;
    Size_t Capacity() const;
    ID_t Teacher() const;
    List<ID_t> Enrolled() const;
    bool IsFull() const;
    bool IsEmpty() const;
    
    bool operator == (ID_t _id);
};

// 在指定课程的签名表中登记学生。
// 【无视非法】该函数不进行合法性验证，使用者需保证合法。
// 【本地异步】该函数仅对本类进行修改，不会同步修改它处。
void Course::Enroll(ID_t _studentId)
{
    enrolled.Append(_studentId);
}

// 将学生从指定课程的签名表中移除。
// 【无视非法】该函数不进行合法性验证，使用者需保证合法。
// 【本地异步】该函数仅对本类进行修改，不会同步修改它处。
void Course::Remove(ID_t _studentId)
{
    enrolled.Remove(_studentId);
}

// 将指定课程分配给指定老师。
// 【无视非法】该函数不进行合法性验证，使用者需保证合法。
// 【本地异步】该函数仅对本类进行修改，不会同步修改它处。
void Course::Assign(ID_t _teacherId)
{
    teacher = _teacherId;
}

Course::Course(ID_t _id, std::string _name, Size_t _capacity, ID_t _teacher)
{
    id = _id;
    name = _name;
    capacity = _capacity;
    teacher = _teacher;
}

// 获取课程 ID。
ID_t Course::ID() const
{
    return id;
}

// 获取课程名称。
std::string Course::Name() const
{
    return name;
}

// 获取课程容量。
Size_t Course::Capacity() const
{
    return capacity;
}

// 获取课程教师。
ID_t Course::Teacher() const
{
    return teacher;
}

// 获取已选学生。
List<ID_t> Course::Enrolled() const
{
    return enrolled;
}

// 判断课程是否已满。
bool Course::IsFull() const
{
    return enrolled.Length() >= capacity;
}

// 判断课程是否为空。
bool Course::IsEmpty() const
{
    return enrolled.Length() == 0;
}

// 重载相等判断，比对课程 ID。
bool Course::operator == (ID_t _id)
{
    return id == _id;
}

#endif