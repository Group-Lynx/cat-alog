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

// ��ָ���γ̵�ǩ�����еǼ�ѧ����
// �����ӷǷ����ú��������кϷ�����֤��ʹ�����豣֤�Ϸ���
// �������첽���ú������Ա�������޸ģ�����ͬ���޸�������
void Course::Enroll(ID_t _studentId)
{
    enrolled.Append(_studentId);
}

// ��ѧ����ָ���γ̵�ǩ�������Ƴ���
// �����ӷǷ����ú��������кϷ�����֤��ʹ�����豣֤�Ϸ���
// �������첽���ú������Ա�������޸ģ�����ͬ���޸�������
void Course::Remove(ID_t _studentId)
{
    enrolled.Remove(_studentId);
}

// ��ָ���γ̷����ָ����ʦ��
// �����ӷǷ����ú��������кϷ�����֤��ʹ�����豣֤�Ϸ���
// �������첽���ú������Ա�������޸ģ�����ͬ���޸�������
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

// ��ȡ�γ� ID��
ID_t Course::ID() const
{
    return id;
}

// ��ȡ�γ����ơ�
std::string Course::Name() const
{
    return name;
}

// ��ȡ�γ�������
Size_t Course::Capacity() const
{
    return capacity;
}

// ��ȡ�γ̽�ʦ��
ID_t Course::Teacher() const
{
    return teacher;
}

// ��ȡ��ѡѧ����
List<ID_t> Course::Enrolled() const
{
    return enrolled;
}

// �жϿγ��Ƿ�������
bool Course::IsFull() const
{
    return enrolled.Length() >= capacity;
}

// �жϿγ��Ƿ�Ϊ�ա�
bool Course::IsEmpty() const
{
    return enrolled.Length() == 0;
}

// ��������жϣ��ȶԿγ� ID��
bool Course::operator == (ID_t _id)
{
    return id == _id;
}

#endif