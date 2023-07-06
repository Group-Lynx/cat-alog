#ifndef DM_EXCEPTION_H
#define DM_EXCEPTION_H

#include <exception>
#include <string>

// δ֪ѧ������ʾ�޷�ͨ��ָ�� ID �ҵ���Ӧѧ����
class UnknownStudent : public std::exception
{
private:
    std::string message;
public:
    UnknownStudent() : message("δ֪ѧ����") {};
    UnknownStudent(const std::string& _msg) : message(_msg) {}
    virtual const char* what() const throw()
    {
        return message.c_str();
    }
};

// δ֪�γ̣���ʾ�޷�ͨ��ָ�� ID �ҵ���Ӧ�γ̡�
class UnknownCourse : public std::exception
{
private:
    std::string message;
public:
    UnknownCourse() : message("δ֪�γ̡�") {};
    UnknownCourse(const std::string& _msg) : message(_msg) {}
    virtual const char* what() const throw()
    {
        return message.c_str();
    }
};

// δ֪��ʦ����ʾ�޷�ͨ��ָ�� ID �ҵ���Ӧ��ʦ��
class UnknownTeacher : public std::exception
{
private:
    std::string message;
public:
    UnknownTeacher() : message("δ֪��ʦ��") {};
    UnknownTeacher(const std::string& _msg) : message(_msg) {}
    virtual const char* what() const throw()
    {
        return message.c_str();
    }
};

// δ֪�û�����ʾ�޷�ͨ��ָ�� ID �ҵ���Ӧ�û���
class UnknownUser : public std::exception
{
private:
    std::string message;
public:
    UnknownUser() : message("δ֪�û���") {};
    UnknownUser(const std::string& _msg) : message(_msg) {}
    virtual const char* what() const throw()
    {
        return message.c_str();
    }
};

// ID �Ѵ��ڣ���ʾ�Ѿ����ڸ� ID �Ķ���
class IDExists : public std::exception
{
private:
    std::string message;
public:
    IDExists() : message("ID �Ѵ��ڡ�") {};
    IDExists(const std::string& _msg) : message(_msg) {}
    virtual const char* what() const throw()
    {
        return message.c_str();
    }
};

// ѧ���ظ�ѡ�Σ���ʾѧ���Ѿ�ѡ���ÿγ̡�
class AlreadyTaken : public std::exception
{
private:
    std::string message;
public:
    AlreadyTaken() : message("�ÿγ���ѡ��") {};
    AlreadyTaken(const std::string& _msg) : message(_msg) {}
    virtual const char* what() const throw()
    {
        return message.c_str();
    }
};

// ��ʦ�ظ��ڿΣ���ʾ��ʦ�Ѿ��ڹ��ÿγ̡�
class AlreadyTaught : public std::exception
{
private:
    std::string message;
public:
    AlreadyTaught() : message("�ÿγ����ڡ�") {};
    AlreadyTaught(const std::string& _msg) : message(_msg) {}
    virtual const char* what() const throw()
    {
        return message.c_str();
    }
};

// ѧ��δ��ѡ�Σ���ʾѧ��δѡ���ÿγ̡�
class NotTaken : public std::exception
{
private:
    std::string message;
public:
    NotTaken() : message("�ÿγ�δѡ��") {};
    NotTaken(const std::string& _msg) : message(_msg) {}
    virtual const char* what() const throw()
    {
        return message.c_str();
    }
};

// ��ʦδ���ڿΣ���ʾ��ʦδ�ڹ��ÿγ̡�
class NotTaught : public std::exception
{
private:
    std::string message;
public:
    NotTaught() : message("�ÿγ�δ�ڡ�") {};
    NotTaught(const std::string& _msg) : message(_msg) {}
    virtual const char* what() const throw()
    {
        return message.c_str();
    }
};

// �γ���������ʾ�γ��Ѿ��ﵽ���ѡ��������
class CourseIsFull : public std::exception
{
private:
    std::string message;
public:
    CourseIsFull() : message("�γ�������") {};
    CourseIsFull(const std::string& _msg) : message(_msg) {}
    virtual const char* what() const throw()
    {
        return message.c_str();
    }
};

// �γ̲��գ���ʾ����ѧ��ѡ�޸ÿγ̡�
class CourseNotFree : public std::exception
{
private:
    std::string message;
public:
    CourseNotFree() : message("�ÿγ�����ѧ����") {};
    CourseNotFree(const std::string& _msg) : message(_msg) {}
    virtual const char* what() const throw()
    {
        return message.c_str();
    }
};

// ѧ���޿գ���ʾѧ���Ѿ�ѡ���˿γ̡�
class StudentNotFree : public std::exception
{
private:
    std::string message;
public:
    StudentNotFree() : message("��ѧ������ѡ�Ρ�") {};
    StudentNotFree(const std::string& _msg) : message(_msg) {}
    virtual const char* what() const throw()
    {
        return message.c_str();
    }
};

// ��ʦ�޿գ���ʾ��ʦ�Ѿ������˿γ̡�
class TeacherNotFree : public std::exception
{
private:
    std::string message;
public:
    TeacherNotFree() : message("�ý�ʦ�����ڿΡ�") {};
    TeacherNotFree(const std::string& _msg) : message(_msg) {}
    virtual const char* what() const throw()
    {
        return message.c_str();
    }
};

// �����𻵣���ʾ�����ļ��Ѿ��𻵡�
class CorruptedData : public std::exception
{
private:
    std::string message;
public:
    CorruptedData() : message("�������𻵡�") {};
    CorruptedData(const std::string& _msg) : message(_msg) {}
    virtual const char* what() const throw()
    {
        return message.c_str();
    }
};

#endif