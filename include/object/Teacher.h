#ifndef TEACHER_H
#define TEACHER_H

#include "../struct/List.h"

class Teacher
{
    friend class DM;
private:
    ID_t id;
    List<ID_t> taught;
private:
    void Attach(ID_t _courseId);
    void Detach(ID_t _courseId);
public:
    Teacher(ID_t _id);
    
    ID_t ID() const;
    List<ID_t> Taught() const;
    bool AlreadyTaught(ID_t _courseId);
    bool IsFree();
    
    bool operator == (ID_t _id);
};

// == ʵ�� == //

// ��ָ���γ̵Ŀκ�������ѽ̿γ̡�
// �����ӷǷ����ú��������кϷ�����֤��ʹ�����豣֤�Ϸ���
// �������첽���ú������Ա�������޸ģ�����ͬ���޸�������
void Teacher::Attach(ID_t _courseId)
{
    taught.Append(_courseId);
}

// ��ָ���γ̵ĿκŴ��ѽ̿γ����Ƴ���
// �����ӷǷ����ú��������кϷ�����֤��ʹ�����豣֤�Ϸ���
// �������첽���ú������Ա�������޸ģ�����ͬ���޸�������
void Teacher::Detach(ID_t _courseId)
{
    taught.Remove(_courseId);
}

Teacher::Teacher(ID_t _id)
{
    id = _id;
}

// ��ȡ��ʦ ID��
ID_t Teacher::ID() const
{
    return id;
}

// ��ȡ�ѽ̿γ̡�
List<ID_t> Teacher::Taught() const
{
    return taught;
}

// �ж���ʦ�Ƿ����ָ���γ̡�
bool Teacher::AlreadyTaught(ID_t _courseId)
{
    return taught.Search(_courseId).has_value();
}

// �ж��Ƿ��Ѿ��̿Ρ�
bool Teacher::IsFree()
{
    return taught.Length() == 0;
}

// ��������жϣ��ȶԽ�ʦ ID��
bool Teacher::operator == (ID_t _id)
{
    return id == _id;
}

#endif