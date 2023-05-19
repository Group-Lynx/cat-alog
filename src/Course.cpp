#include "Course.h"
#include <iostream>
#include <string>
using namespace std;
//类外实现
list<Course> Course::courses = list<Course>();
static list<Course> AllCourses()
{
    return Course::courses;
}
Course::Teacher TaughtTeacher()
{
    return teacher; //返回教授这门课的老师。
}
list<Course::Student> EnrolledStudents()
{
    return enrolled;
}
//构造及析构函数
Course::Course(CourseType _category, unsigned int _courseId, Teacher _teacher)
{
    category = _category;
    courseId = _courseId;
    teacher = _teacher;
}
Course::~Course(){}
Course::Course(const Course& _course)
{
    category = _course.category;
    courseId = _course.courseId;
    teacher = _course.teacher;
}
//=运算符重载
Course& Course::operator=(const Course& _course)
{
    category = _course.category;
    courseId = _course.courseId;
    teacher = _course.teacher;
    return *this;
}




