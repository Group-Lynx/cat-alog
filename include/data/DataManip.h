#ifndef DATA_MANIP_H
#define DATA_MANIP_H

#include "../utility/LynType.h"
#include "../utility/Crypto.h"
#include "../utility/IOHandle.h"
#include "../utility/FileHandle.h"
#include "../utility/ValidString.h"

#include "../struct/List.h"

#include "../object/Course.h"
#include "../object/Student.h"
#include "../object/Teacher.h"
#include "../object/User.h"

#include "../data/DMException.h"

// == 声明 == //

// Data Manipulator - 数据操纵器
class DM
{
    friend void Initialize();
    friend void Finalize();
    friend void FactoryReset();
public:
    DM() = delete;
    DM(DM &&) = delete;
    DM(const DM& _obj) = delete;
    ~DM() = delete;

private:
    static List<User> users;
    static List<Course> courses;
    static List<Student> students;
    static List<Teacher> teachers;
    static const std::string storageRoot;
public:
    static List<User> AllUsers();
    static List<Course> AllCourses();
    static List<Student> AllStudents();
    static List<Teacher> AllTeachers();
    
    static bool HasUser(ID_t _userId);
    static bool HasCourse(ID_t _courseId);
    static bool HasStudent(ID_t _courseId);
    static bool HasTeacher(ID_t _courseId);
    
    static User& GetUser(ID_t _userId);
    static Course& GetCourse(ID_t _courseId);
    static Student& GetStudent(ID_t _studentId);
    static Teacher& GetTeacher(ID_t _teacherId);
    
    static void Enroll(ID_t _studentId, ID_t _courseId);
    static void Remove(ID_t _studentId, ID_t _courseId);
    static void Assign(ID_t _teacherId, ID_t _courseId);
    
    static void AddCourse(Course _course);
    static void AddStudent(Student _student, std::string _name);
    static void AddTeacher(Teacher _teacher, std::string _name);
    
    static void RemoveCourse(ID_t _courseId);
    static void RemoveStudent(ID_t _studentId);
    static void RemoveTeacher(ID_t _teacherId);
    
private:
    static bool Load();
    static void LoadCourse(std::string _courseFilePath);
    static void LoadUser(std::string _userFilePath);
    static void LoadStudentCourse(ID_t _id, std::string _line);
    static void LoadTeacherCourse(ID_t _id, std::string _line);
public:
    static void Save();
private:
    static void SaveCourse(std::string _courseFilePath);
    static void SaveUser(std::string _userFilePath);
    static void SaveStudentCourse(std::fstream& _userFile, Student _stu);
    static void SaveTeacherCourse(std::fstream& _userFile, Teacher _tch);
    
    static void AddUser(User _user);
    static void RemoveUser(ID_t _userId);
};

// == 定义 == //

List<User> DM::users;
List<Course> DM::courses;
List<Student> DM::students;
List<Teacher> DM::teachers;
#ifdef _WIN32
const std::string DM::storageRoot = "./";
#else
const std::string DM::storageRoot = "./";
#endif

// == 实现 == //

// 获取所有用户。
List<User> DM::AllUsers() { return users; }
// 获取所有课程。
List<Course> DM::AllCourses() { return courses; }
// 获取所有学生。
List<Student> DM::AllStudents() { return students; }
// 获取所有老师。
List<Teacher> DM::AllTeachers() { return teachers; }

// 依据用户 ID 查询是否存在该用户。
bool DM::HasUser(ID_t _userId)
{
    return users.Search(_userId).has_value();
}

// 依据课程 ID 查询是否存在该课程。
bool DM::HasCourse(ID_t _courseId)
{
    return courses.Search(_courseId).has_value();
}

// 依据学生 ID 查询是否存在该学生。
bool DM::HasStudent(ID_t _studentId)
{
    return students.Search(_studentId).has_value();
}

// 依据老师 ID 查询是否存在该老师。
bool DM::HasTeacher(ID_t _teacherId)
{
    return teachers.Search(_teacherId).has_value();
}

// 依据用户 ID 获取用户。
User& DM::GetUser(ID_t _userId)
{
    if (!HasUser(_userId)) { throw UnknownUser(); }
    
    return users[users.Trieve(_userId).value()];
}

// 依据课程 ID 获取课程。
Course& DM::GetCourse(ID_t _courseId)
{
    if (!HasCourse(_courseId)) { throw UnknownCourse(); }
    
    return courses[courses.Trieve(_courseId).value()];
}

// 依据学生 ID 获取学生。
Student& DM::GetStudent(ID_t _studentId)
{
    if (!HasStudent(_studentId)) { throw UnknownStudent(); }
    
    return students[students.Trieve(_studentId).value()];
}

// 依据老师 ID 获取老师。
Teacher& DM::GetTeacher(ID_t _teacherId)
{
    if (!HasTeacher(_teacherId)) { throw UnknownTeacher(); }
    
    return teachers[teachers.Trieve(_teacherId).value()];
}

// 为学生注册指定课程。
void DM::Enroll(ID_t _studentId, ID_t _courseId)
{
    if (!HasStudent(_studentId)) { throw UnknownStudent(); }
    if (!HasCourse(_courseId)) { throw UnknownCourse(); }
    
    Student& student = students[students.Trieve(_studentId).value()];
    Course& course = courses[courses.Trieve(_courseId).value()];
    
    if (student.AlreadyTaken(_courseId)) { throw AlreadyTaken(); }
    if (course.IsFull()) { throw CourseIsFull(); }
    
    student.Take(_courseId);
    course.Enroll(_studentId);
}

// 将学生从指定课程注销。
void DM::Remove(ID_t _studentId, ID_t _courseId)
{
    if (!HasStudent(_studentId)) { throw UnknownStudent(); }
    if (!HasCourse(_courseId)) { throw UnknownCourse(); }
    
    Student& student = students[students.Trieve(_studentId).value()];
    Course& course = courses[courses.Trieve(_courseId).value()];
    
    if (!student.AlreadyTaken(_courseId)) { throw NotTaken(); }
    
    student.Drop(_courseId);
    course.Remove(_studentId);
}

// 为老师指定课程。
void DM::Assign(ID_t _teacherId, ID_t _courseId)
{
    if (!HasTeacher(_teacherId)) { throw UnknownTeacher(); }
    if (!HasCourse(_courseId)) { throw UnknownCourse(); }
    
    Course& course = courses[courses.Trieve(_courseId).value()];
    Teacher& oldteacher = teachers[teachers.Trieve(course.Teacher()).value()];
    Teacher& newTeacher = teachers[teachers.Trieve(_teacherId).value()];
    
    if (newTeacher.AlreadyTaught(_courseId)) { throw AlreadyTaught(); }
    
    oldteacher.Detach(_courseId);
    newTeacher.Attach(_courseId);
    course.Assign(_teacherId);
}

// 添加课程。
void DM::AddCourse(Course _course)
{
    if (HasCourse(_course.ID())) { throw IDExists(); }
    
    Teacher& teacher = teachers[teachers.Trieve(_course.Teacher()).value()];
    
    teacher.Attach(_course.ID());
    courses.Append(_course);
}

// 添加学生。
void DM::AddStudent(Student _student, std::string _name)
{
    if (HasStudent(_student.ID())) { throw IDExists(); }
    
    students.Append(_student);
    
    std::string id = std::to_string(_student.ID());
    User user(UserType::study, _student.ID(), _name, SSP::Encrypt(id));
    users.Append(user);
}

// 添加老师。
void DM::AddTeacher(Teacher _teacher, std::string _name)
{
    if (HasTeacher(_teacher.ID())) { throw IDExists(); }
    
    teachers.Append(_teacher);
    
    std::string id = std::to_string(_teacher.ID());
    User user(UserType::teach, _teacher.ID(), _name, SSP::Encrypt(id));
    users.Append(user);

}

// 移除课程。
void DM::RemoveCourse(ID_t _courseId)
{
    if (!HasCourse(_courseId)) { throw UnknownCourse(); }
    if (!courses[courses.Trieve(_courseId).value()].IsEmpty()) { throw CourseNotFree(); }
    
    Course& course = courses[courses.Trieve(_courseId).value()];
    Teacher& teacher = teachers[teachers.Trieve(course.Teacher()).value()];
    
    teacher.Detach(_courseId);
    courses.Remove(_courseId);
}

// 移除学生。
void DM::RemoveStudent(ID_t _studentId)
{
    if (!HasStudent(_studentId)) { throw UnknownStudent(); }
    if (!students[students.Trieve(_studentId).value()].IsFree()) { throw StudentNotFree(); }
    
    students.Remove(_studentId);
    users.Remove(_studentId);
}

// 移除老师。
void DM::RemoveTeacher(ID_t _teacherId)
{
    if (!HasTeacher(_teacherId)) { throw UnknownTeacher(); }
    if (!teachers[teachers.Trieve(_teacherId).value()].IsFree()) { throw TeacherNotFree(); }
    
    teachers.Remove(_teacherId);
    users.Remove(_teacherId);
}

// 添加用户。
// 【特例操作】该函数为特殊操作保留，不应当被直接调用。
void DM::AddUser(User _user)
{
    if (HasUser(_user.ID())) { throw IDExists(); }
    
    users.Append(_user);
}

// 移除用户。
// 【特例操作】该函数为特殊操作保留，不应当被直接调用。
void DM::RemoveUser(ID_t _userId)
{
    if (!HasUser(_userId)) { throw UnknownUser(); }
    
    users.Remove(_userId);
}

// 加载数据。
bool DM::Load()
{
    std::string rootFilePath = FH::CombinePath(storageRoot, "root.lyn");
    std::fstream rootFile(rootFilePath, std::ios::in);
    if (!rootFile.good()) { return false; }
    
    std::string courseFilePath, courseVerifyCode;
    rootFile >> courseFilePath >> courseVerifyCode;
    if (!FH::Validate(courseFilePath, courseVerifyCode)) { throw CorruptedData(); }
    
    std::string userFilePath, userVerifyCode;
    rootFile >> userFilePath >> userVerifyCode;
    if (!FH::Validate(userFilePath, userVerifyCode)) { throw CorruptedData(); }
    
    rootFile.close();
    
    LoadCourse(courseFilePath);
    LoadUser(userFilePath);
    
    return true;
}

// 加载课程信息。
void DM::LoadCourse(std::string _courseFilePath)
{
    std::fstream courseFile(_courseFilePath, std::ios::in);
    
    ID_t id;
    Size_t capacity;
    ID_t teacher;
    std::string name;
    
    std::string line;
    size_t pos;
    while (!courseFile.eof())
    {
        std::getline(courseFile, line);
        if (VS::IsWhiteString(line)) { break; }
        
        pos = line.find(":");
        id = std::stoll(line.substr(0, pos));
        line = line.substr(pos + 1);
        
        pos = line.find(":");
        capacity = std::stoll(line.substr(0, pos));
        line = line.substr(pos + 1);
        
        pos = line.find(":");
        teacher = std::stoll(line.substr(0, pos));
        name = line.substr(pos + 1);
        
        courses.Append(Course(id, name, capacity, teacher));
        
        std::getline(courseFile, line);
        if (VS::IsWhiteString(line)) { continue; }
        Course& course = courses[courses.Length() - 1];
        while ((pos = line.find(":")) != std::string::npos)
        {
            course.enrolled.Append(std::stoi(line.substr(0, pos)));
            line = line.substr(pos + 1);
        }
        course.enrolled.Append(std::stoi(line));
    }
    
    courseFile.close();
}

// 加载用户信息。
void DM::LoadUser(std::string _userFilePath)
{
    std::fstream userFile(_userFilePath, std::ios::in);
    
    UserType type;
    ID_t id;
    std::string pswd;
    std::string name;
    
    std::string line;
    size_t pos;
    while (!userFile.eof())
    {
        std::getline(userFile, line);
        if (VS::IsWhiteString(line)) { break; }
        
        pos = line.find(":");
        type = static_cast<UserType>(std::stoi(line.substr(0, pos)));
        line = line.substr(pos + 1);
        
        pos = line.find(":");
        id = std::stoll(line.substr(0, pos));
        line = line.substr(pos + 1);
        
        pos = line.find(":");
        pswd = line.substr(0, pos);
        name = line.substr(pos + 1);
        
        users.Append(User(type, id, name, pswd));
        
        std::getline(userFile, line);
        switch (type)
        {
        case UserType::admin:
            break;
        case UserType::study:
            LoadStudentCourse(id, line);
            break;
        case UserType::teach:
            LoadTeacherCourse(id, line);
            break;
        }
    }
    
    userFile.close();
}

// 加载学生选课信息。
void DM::LoadStudentCourse(ID_t _id, std::string _line)
{
    if (VS::IsWhiteString(_line))
    {
        students.Append(Student(_id));
        return;
    }
    
    ID_t cid;
    size_t pos;
    
    Student stu(_id);
    while ((pos = _line.find(":")) != std::string::npos)
    {
        cid = std::stoi(_line.substr(0, pos));
        _line = _line.substr(pos + 1);
        stu.selected.Append(cid);
    }
    cid = std::stoi(_line);
    stu.selected.Append(cid);
    students.Append(stu);
}

// 加载老师所教课程。
void DM::LoadTeacherCourse(ID_t _id, std::string _line)
{
    if (VS::IsWhiteString(_line))
    {
        teachers.Append(Teacher(_id));
        return;
    }
    
    ID_t cid;
    size_t pos;
    
    Teacher tch(_id);
    while ((pos = _line.find(":")) != std::string::npos)
    {
        cid = std::stoi(_line.substr(0, pos));
        _line = _line.substr(pos + 1);
        tch.taught.Append(cid);
    }
    cid = std::stoi(_line);
    tch.taught.Append(cid);
    teachers.Append(tch);
}

// 保存数据。
void DM::Save()
{
    std::string rootFilePath = FH::CombinePath(storageRoot, "root.lyn");
    std::fstream rootFile(rootFilePath, std::ios::in);
    if (!rootFile.good())
    {
        rootFile = std::fstream(rootFilePath, std::ios::out);
        rootFile << FH::CombinePath(storageRoot, "course.lyn") << " " << SSP::Encrypt("") << std::endl;
        rootFile << FH::CombinePath(storageRoot, "user.lyn") << " " << SSP::Encrypt("") << std::endl;
        rootFile.close();
        rootFile = std::fstream(rootFilePath, std::ios::in);
    }
    std::string courseFilePath, courseVerifyCode;
    std::string userFilePath, userVerifyCode;
    rootFile >> courseFilePath >> courseVerifyCode;
    rootFile >> userFilePath >> userVerifyCode;
    rootFile.close();
    
    SaveCourse(courseFilePath);
    SaveUser(userFilePath);
    
    rootFile = std::fstream(rootFilePath, std::ios::out);
    rootFile << courseFilePath << " " << FH::Signature(courseFilePath) << std::endl;
    rootFile << userFilePath << " " << FH::Signature(userFilePath) << std::endl;
    rootFile.close();
}

// 保存课程信息。
void DM::SaveCourse(std::string _courseFilePath)
{
    std::fstream courseFile(_courseFilePath, std::ios::out);
    
    for (int i = 0; i < courses.Length(); i++)
    {
        courseFile << courses[i].id << ":"
                   << courses[i].capacity << ":"
                   << courses[i].teacher << ":"
                   << courses[i].name << std::endl;
        for (int j = 0; j < courses[i].enrolled.Length(); j++)
        {
            courseFile << courses[i].enrolled[j] << ((j == courses[i].enrolled.Length() - 1) ? "" : ":");
        }
        courseFile << std::endl;
    }
    
    courseFile.close();
}

// 保存用户信息。
void DM::SaveUser(std::string _userFilePath)
{
    std::fstream userFile(_userFilePath, std::ios::out);
    
    for (int i = 0; i < users.Length(); i++)
    {
        userFile << static_cast<int>(users[i].type) << ":"
                 << users[i].id << ":"
                 << users[i].pswd << ":"
                 << users[i].name << std::endl;
        switch (users[i].type)
        {
        case UserType::admin:
            userFile << std::endl;
            break;
        case UserType::study:
            SaveStudentCourse(userFile, students.Search(users[i].id).value());
            break;
        case UserType::teach:
            SaveTeacherCourse(userFile, teachers.Search(users[i].id).value());
            break;
        }
    }
}

// 保存学生选课信息。
void DM::SaveStudentCourse(std::fstream& _userFile, Student _stu)
{
    int length = _stu.selected.Length();
    for (int i = 0; i < length; i++)
    {
        _userFile << _stu.selected[i] << ((i == length - 1) ? "" : ":");
    }
    _userFile << std::endl;
}

// 保存老师所教课程。
void DM::SaveTeacherCourse(std::fstream& _userFile, Teacher _tch)
{
    int length = _tch.taught.Length();
    for (int i = 0; i < length; i++)
    {
        _userFile << _tch.taught[i] << ((i == length - 1) ? "" : ":");
    }
    _userFile << std::endl;
}

#endif