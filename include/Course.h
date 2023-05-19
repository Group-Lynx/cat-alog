#ifndef COURSE_H
#define COURSE_H
#include <list>
#include <Student.h>
#include <Teacher.h>

//类外实现课程类型
enum CourseType 
{
    MATH, COMP, BIOL, PHYS, STAT, EXTN, GENE//数学、计算机、生物、物理、统计学、电子科学与技术、通识教育
};
//类的实现
class Course
{
private:
    //属性
    static list<Course> courses;  //用于存储所有的课程。
    list<Student> enrolled;  //用于存储选择了这门课的学生。
    Teacher teacher;  //用于存储教授这门课的老师。
    CourseType category;  //表示课程的分类。
    unsigned int courseId;  //用于存储这门课的课号。
public:
    //函数
    static list<Course> AllCourses();  //返回所有的课程的列表。
    Teacher TaughtTeacher();  //返回教授这门课的老师。 
    list<Student> EnrolledStudents(); //返回选择了这门课的学生。
    //构造及析构函数
    Course(CourseType _category, unsigned int _courseId, Teacher _teacher);
    ~Course();
    Course(const Course& _course);
    //=运算符重载
    Course& operator=(const Course& _course);
};


#endif