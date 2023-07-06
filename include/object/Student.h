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

// == ʵ�� == //

// ��ָ���γ̵Ŀκ��������ѡ�γ̡�
// �����ӷǷ����ú��������кϷ�����֤��ʹ�����豣֤�Ϸ���
// �������첽���ú������Ա�������޸ģ�����ͬ���޸�������
void Student::Take(ID_t _courseId)
{
    selected.Append(_courseId);
}

// ��ָ���γ̵ĿκŴ���ѡ�γ����Ƴ���
// �����ӷǷ����ú��������кϷ�����֤��ʹ�����豣֤�Ϸ���
// �������첽���ú������Ա�������޸ģ�����ͬ���޸�������
void Student::Drop(ID_t _courseId)
{
    selected.Remove(_courseId);
}

Student::Student(ID_t _id)
{
    id = _id;
}

// ��ȡѧ�� ID��
ID_t Student::ID() const
{
    return id;
}

// ��ȡ��ѡ�γ̡�
List<ID_t> Student::Selected() const
{
    return selected;
}

// �ж��Ƿ��Ѿ�ע���ָ���γ̡�
bool Student::AlreadyTaken(ID_t _courseId)
{
    return selected.Search(_courseId).has_value();
}

// �ж��Ƿ��Ѿ�ѡ�Ρ�
bool Student::IsFree()
{
    return selected.Length() == 0;
}

// ��������жϣ��ȶ�ѧ�� ID��
bool Student::operator == (ID_t _id)
{
    return id == _id;
}

#endif