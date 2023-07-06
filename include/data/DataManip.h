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

// == ���� == //

// Data Manipulator - ���ݲ�����
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

// == ���� == //

List<User> DM::users;
List<Course> DM::courses;
List<Student> DM::students;
List<Teacher> DM::teachers;
#ifdef _WIN32
const std::string DM::storageRoot = "./";
#else
const std::string DM::storageRoot = "./";
#endif

// == ʵ�� == //

// ��ȡ�����û���
List<User> DM::AllUsers() { return users; }
// ��ȡ���пγ̡�
List<Course> DM::AllCourses() { return courses; }
// ��ȡ����ѧ����
List<Student> DM::AllStudents() { return students; }
// ��ȡ������ʦ��
List<Teacher> DM::AllTeachers() { return teachers; }

// �����û� ID ��ѯ�Ƿ���ڸ��û���
bool DM::HasUser(ID_t _userId)
{
    return users.Search(_userId).has_value();
}

// ���ݿγ� ID ��ѯ�Ƿ���ڸÿγ̡�
bool DM::HasCourse(ID_t _courseId)
{
    return courses.Search(_courseId).has_value();
}

// ����ѧ�� ID ��ѯ�Ƿ���ڸ�ѧ����
bool DM::HasStudent(ID_t _studentId)
{
    return students.Search(_studentId).has_value();
}

// ������ʦ ID ��ѯ�Ƿ���ڸ���ʦ��
bool DM::HasTeacher(ID_t _teacherId)
{
    return teachers.Search(_teacherId).has_value();
}

// �����û� ID ��ȡ�û���
User& DM::GetUser(ID_t _userId)
{
    if (!HasUser(_userId)) { throw UnknownUser(); }
    
    return users[users.Trieve(_userId).value()];
}

// ���ݿγ� ID ��ȡ�γ̡�
Course& DM::GetCourse(ID_t _courseId)
{
    if (!HasCourse(_courseId)) { throw UnknownCourse(); }
    
    return courses[courses.Trieve(_courseId).value()];
}

// ����ѧ�� ID ��ȡѧ����
Student& DM::GetStudent(ID_t _studentId)
{
    if (!HasStudent(_studentId)) { throw UnknownStudent(); }
    
    return students[students.Trieve(_studentId).value()];
}

// ������ʦ ID ��ȡ��ʦ��
Teacher& DM::GetTeacher(ID_t _teacherId)
{
    if (!HasTeacher(_teacherId)) { throw UnknownTeacher(); }
    
    return teachers[teachers.Trieve(_teacherId).value()];
}

// Ϊѧ��ע��ָ���γ̡�
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

// ��ѧ����ָ���γ�ע����
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

// Ϊ��ʦָ���γ̡�
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

// ��ӿγ̡�
void DM::AddCourse(Course _course)
{
    if (HasCourse(_course.ID())) { throw IDExists(); }
    
    Teacher& teacher = teachers[teachers.Trieve(_course.Teacher()).value()];
    
    teacher.Attach(_course.ID());
    courses.Append(_course);
}

// ���ѧ����
void DM::AddStudent(Student _student, std::string _name)
{
    if (HasStudent(_student.ID())) { throw IDExists(); }
    
    students.Append(_student);
    
    std::string id = std::to_string(_student.ID());
    User user(UserType::study, _student.ID(), _name, SSP::Encrypt(id));
    users.Append(user);
}

// �����ʦ��
void DM::AddTeacher(Teacher _teacher, std::string _name)
{
    if (HasTeacher(_teacher.ID())) { throw IDExists(); }
    
    teachers.Append(_teacher);
    
    std::string id = std::to_string(_teacher.ID());
    User user(UserType::teach, _teacher.ID(), _name, SSP::Encrypt(id));
    users.Append(user);

}

// �Ƴ��γ̡�
void DM::RemoveCourse(ID_t _courseId)
{
    if (!HasCourse(_courseId)) { throw UnknownCourse(); }
    if (!courses[courses.Trieve(_courseId).value()].IsEmpty()) { throw CourseNotFree(); }
    
    Course& course = courses[courses.Trieve(_courseId).value()];
    Teacher& teacher = teachers[teachers.Trieve(course.Teacher()).value()];
    
    teacher.Detach(_courseId);
    courses.Remove(_courseId);
}

// �Ƴ�ѧ����
void DM::RemoveStudent(ID_t _studentId)
{
    if (!HasStudent(_studentId)) { throw UnknownStudent(); }
    if (!students[students.Trieve(_studentId).value()].IsFree()) { throw StudentNotFree(); }
    
    students.Remove(_studentId);
    users.Remove(_studentId);
}

// �Ƴ���ʦ��
void DM::RemoveTeacher(ID_t _teacherId)
{
    if (!HasTeacher(_teacherId)) { throw UnknownTeacher(); }
    if (!teachers[teachers.Trieve(_teacherId).value()].IsFree()) { throw TeacherNotFree(); }
    
    teachers.Remove(_teacherId);
    users.Remove(_teacherId);
}

// ����û���
// �������������ú���Ϊ���������������Ӧ����ֱ�ӵ��á�
void DM::AddUser(User _user)
{
    if (HasUser(_user.ID())) { throw IDExists(); }
    
    users.Append(_user);
}

// �Ƴ��û���
// �������������ú���Ϊ���������������Ӧ����ֱ�ӵ��á�
void DM::RemoveUser(ID_t _userId)
{
    if (!HasUser(_userId)) { throw UnknownUser(); }
    
    users.Remove(_userId);
}

// �������ݡ�
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

// ���ؿγ���Ϣ��
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

// �����û���Ϣ��
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

// ����ѧ��ѡ����Ϣ��
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

// ������ʦ���̿γ̡�
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

// �������ݡ�
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

// ����γ���Ϣ��
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

// �����û���Ϣ��
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

// ����ѧ��ѡ����Ϣ��
void DM::SaveStudentCourse(std::fstream& _userFile, Student _stu)
{
    int length = _stu.selected.Length();
    for (int i = 0; i < length; i++)
    {
        _userFile << _stu.selected[i] << ((i == length - 1) ? "" : ":");
    }
    _userFile << std::endl;
}

// ������ʦ���̿γ̡�
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