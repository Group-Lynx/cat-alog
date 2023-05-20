#ifndef TEACHER_H
#define TEACHER_H

#include "User.h"
#include "Course.h"
#include "List.h"

class Teacher : public User
{
public:
    static List<Teacher> teacherList;
    List<Course> courseList;

    List<Teacher> AllTeachers()
    {
        return teacherList;
    }
    void AddCourse(Course _course)
    {
        courseList.AppendNode(_course);
    }

    void DelCourse(Course _course)
    {
        int index = _course.SeekNode(course);
        if (index >= 0)
        {
            courseList.DeleteNode(index);
        }
    }
    void ModCourse(Course _course)
    {
        int index = _course.SeekNode(course);
        if (index >= 0)
        {
            courseList[index] = course;
        }
    }
};

#endif
