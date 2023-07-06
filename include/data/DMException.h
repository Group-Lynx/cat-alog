#ifndef DM_EXCEPTION_H
#define DM_EXCEPTION_H

#include <exception>
#include <string>

// 未知学生，表示无法通过指定 ID 找到对应学生。
class UnknownStudent : public std::exception
{
private:
    std::string message;
public:
    UnknownStudent() : message("未知学生。") {};
    UnknownStudent(const std::string& _msg) : message(_msg) {}
    virtual const char* what() const throw()
    {
        return message.c_str();
    }
};

// 未知课程，表示无法通过指定 ID 找到对应课程。
class UnknownCourse : public std::exception
{
private:
    std::string message;
public:
    UnknownCourse() : message("未知课程。") {};
    UnknownCourse(const std::string& _msg) : message(_msg) {}
    virtual const char* what() const throw()
    {
        return message.c_str();
    }
};

// 未知老师，表示无法通过指定 ID 找到对应老师。
class UnknownTeacher : public std::exception
{
private:
    std::string message;
public:
    UnknownTeacher() : message("未知教师。") {};
    UnknownTeacher(const std::string& _msg) : message(_msg) {}
    virtual const char* what() const throw()
    {
        return message.c_str();
    }
};

// 未知用户，表示无法通过指定 ID 找到对应用户。
class UnknownUser : public std::exception
{
private:
    std::string message;
public:
    UnknownUser() : message("未知用户。") {};
    UnknownUser(const std::string& _msg) : message(_msg) {}
    virtual const char* what() const throw()
    {
        return message.c_str();
    }
};

// ID 已存在，表示已经存在该 ID 的对象。
class IDExists : public std::exception
{
private:
    std::string message;
public:
    IDExists() : message("ID 已存在。") {};
    IDExists(const std::string& _msg) : message(_msg) {}
    virtual const char* what() const throw()
    {
        return message.c_str();
    }
};

// 学生重复选课，表示学生已经选过该课程。
class AlreadyTaken : public std::exception
{
private:
    std::string message;
public:
    AlreadyTaken() : message("该课程已选。") {};
    AlreadyTaken(const std::string& _msg) : message(_msg) {}
    virtual const char* what() const throw()
    {
        return message.c_str();
    }
};

// 老师重复授课，表示老师已经授过该课程。
class AlreadyTaught : public std::exception
{
private:
    std::string message;
public:
    AlreadyTaught() : message("该课程已授。") {};
    AlreadyTaught(const std::string& _msg) : message(_msg) {}
    virtual const char* what() const throw()
    {
        return message.c_str();
    }
};

// 学生未曾选课，表示学生未选过该课程。
class NotTaken : public std::exception
{
private:
    std::string message;
public:
    NotTaken() : message("该课程未选。") {};
    NotTaken(const std::string& _msg) : message(_msg) {}
    virtual const char* what() const throw()
    {
        return message.c_str();
    }
};

// 老师未曾授课，表示老师未授过该课程。
class NotTaught : public std::exception
{
private:
    std::string message;
public:
    NotTaught() : message("该课程未授。") {};
    NotTaught(const std::string& _msg) : message(_msg) {}
    virtual const char* what() const throw()
    {
        return message.c_str();
    }
};

// 课程已满，表示课程已经达到最大选课人数。
class CourseIsFull : public std::exception
{
private:
    std::string message;
public:
    CourseIsFull() : message("课程已满。") {};
    CourseIsFull(const std::string& _msg) : message(_msg) {}
    virtual const char* what() const throw()
    {
        return message.c_str();
    }
};

// 课程不空，表示存在学生选修该课程。
class CourseNotFree : public std::exception
{
private:
    std::string message;
public:
    CourseNotFree() : message("该课程已有学生。") {};
    CourseNotFree(const std::string& _msg) : message(_msg) {}
    virtual const char* what() const throw()
    {
        return message.c_str();
    }
};

// 学生无空，表示学生已经选修了课程。
class StudentNotFree : public std::exception
{
private:
    std::string message;
public:
    StudentNotFree() : message("该学生已有选课。") {};
    StudentNotFree(const std::string& _msg) : message(_msg) {}
    virtual const char* what() const throw()
    {
        return message.c_str();
    }
};

// 老师无空，表示老师已经教授了课程。
class TeacherNotFree : public std::exception
{
private:
    std::string message;
public:
    TeacherNotFree() : message("该教师已有授课。") {};
    TeacherNotFree(const std::string& _msg) : message(_msg) {}
    virtual const char* what() const throw()
    {
        return message.c_str();
    }
};

// 数据损坏，表示数据文件已经损坏。
class CorruptedData : public std::exception
{
private:
    std::string message;
public:
    CorruptedData() : message("数据已损坏。") {};
    CorruptedData(const std::string& _msg) : message(_msg) {}
    virtual const char* what() const throw()
    {
        return message.c_str();
    }
};

#endif