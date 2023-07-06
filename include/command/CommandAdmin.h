#ifndef COMMAND_ADM_H
#define COMMAND_ADM_H

#include "../data/DataManip.h"

#include "../utility/IOHandle.h"
#include "../utility/ValidString.h"

#include "../data/GlobalVariable.h"

bool Execute(std::function<void()> _func);

namespace ADM
{
    void Construct(CTree& _root);
    
    void None();
    void Help();
    void Save();
    void Script();
    void Pswd();
    void Logout();
    void Exit();
    
    namespace USER
    {
        void Help();
        void View();
        void Pswd();
        void Detail();
        void Create();
        void Delete();
        
        void Display(ID_t _uid);
        std::string Peek(ID_t _uid);
        
        void DetailArg();
        void CreateArg();
        void DeleteArg();
    }
    
    namespace COURSE
    {
        void Help();
        void View();
        void Detail();
        void Create();
        void Delete();
        void Assign();
        void Enroll();
        void Remove();
        
        void Display(ID_t _cid);
        std::string Peek(ID_t _cid);
        
        void DetailArg();
        void CreateArg();
        void DeleteArg();
        void AssignArg();
        void EnrollArg();
        void RemoveArg();
    }
}

// ����������
void ADM::Construct(CTree& _root)
{
    std::unique_ptr<CTree> _user = std::make_unique<CTree>(CTree("user", USER::Help));
    _user->Grow(std::make_unique<CTree>(CTree("help", USER::Help)));
    _user->Grow(std::make_unique<CTree>(CTree("view", USER::View)));
    _user->Grow(std::make_unique<CTree>(CTree("pswd", USER::Pswd)));
    
    std::unique_ptr<CTree> _usr_detail = std::make_unique<CTree>(CTree("detail", USER::Detail));
    _usr_detail->Grow(std::make_unique<CTree>(CTree("-arg", USER::DetailArg)));
    _user->Grow(std::move(_usr_detail));
    
    std::unique_ptr<CTree> _usr_create = std::make_unique<CTree>(CTree("create", USER::Create));
    _usr_create->Grow(std::make_unique<CTree>(CTree("-arg", USER::CreateArg)));
    _user->Grow(std::move(_usr_create));
    
    std::unique_ptr<CTree> _usr_delete = std::make_unique<CTree>(CTree("delete", USER::Delete));
    _usr_delete->Grow(std::make_unique<CTree>(CTree("-arg", USER::DeleteArg)));
    _user->Grow(std::move(_usr_delete));
    
    _root.Grow(std::move(_user));
    
    std::unique_ptr<CTree> _course = std::make_unique<CTree>(CTree("course", COURSE::Help));
    _course->Grow(std::make_unique<CTree>(CTree("help", COURSE::Help)));
    _course->Grow(std::make_unique<CTree>(CTree("view", COURSE::View)));
    
    std::unique_ptr<CTree> _crs_detail = std::make_unique<CTree>(CTree("detail", COURSE::Detail));
    _crs_detail->Grow(std::make_unique<CTree>(CTree("-arg", COURSE::DetailArg)));
    _course->Grow(std::move(_crs_detail));
    
    std::unique_ptr<CTree> _crs_create = std::make_unique<CTree>(CTree("create", COURSE::Create));
    _crs_create->Grow(std::make_unique<CTree>(CTree("-arg", COURSE::CreateArg)));
    _course->Grow(std::move(_crs_create));
    
    std::unique_ptr<CTree> _crs_delete = std::make_unique<CTree>(CTree("delete", COURSE::Delete));
    _crs_delete->Grow(std::make_unique<CTree>(CTree("-arg", COURSE::DeleteArg)));
    _course->Grow(std::move(_crs_delete));
    
    std::unique_ptr<CTree> _crs_assign = std::make_unique<CTree>(CTree("assign", COURSE::Assign));
    _crs_assign->Grow(std::make_unique<CTree>(CTree("-arg", COURSE::AssignArg)));
    _course->Grow(std::move(_crs_assign));
    
    std::unique_ptr<CTree> _crs_enroll = std::make_unique<CTree>(CTree("enroll", COURSE::Enroll));
    _crs_enroll->Grow(std::make_unique<CTree>(CTree("-arg", COURSE::EnrollArg)));
    _course->Grow(std::move(_crs_enroll));
    
    std::unique_ptr<CTree> _crs_remove = std::make_unique<CTree>(CTree("remove", COURSE::Remove));
    _crs_remove->Grow(std::make_unique<CTree>(CTree("-arg", COURSE::RemoveArg)));
    _course->Grow(std::move(_crs_remove));
    _root.Grow(std::move(_course));
    
    _root.Grow(std::make_unique<CTree>(CTree("help", Help)));
    _root.Grow(std::make_unique<CTree>(CTree("save", Save)));
    _root.Grow(std::make_unique<CTree>(CTree("script", Script)));
    _root.Grow(std::make_unique<CTree>(CTree("pswd", Pswd)));
    _root.Grow(std::make_unique<CTree>(CTree("logout", Logout)));
    _root.Grow(std::make_unique<CTree>(CTree("exit", Exit)));
}

// ��Ч���
void ADM::None()
{
    IO::ERROR("δ֪������� `help` �Ի�ȡ������Ϣ��");
}

// ������Ϣ��
void ADM::Help()
{
    IO::PRINT("�������");
    IO::PRINT("  help    - ��ʾ��������Ϣ");
    IO::PRINT("  save    - ��������");
    IO::PRINT("  pswd    - ��������");
    IO::PRINT("  logout  - �˳���ǰ�û�");
    IO::PRINT("  exit    - �˳�����");
    IO::PRINT("  user    - ִ���û�����");
    IO::PRINT("  course  - ִ�пγ̹���");
    IO::PRINT("�ű��Զ�����");
    IO::PRINT("  script        - ���нű��ļ�");
    IO::PRINT("  script [path] - �� [path] ��ִ�нű��ļ�");
}

// �������ݡ�
void ADM::Save()
{
    IO::MESSG("�������ݡ�����");
    DM::Save();
    IO::MESSG("�����ѱ��档");
}

// �ű�����
void ADM::Script()
{
    std::string path;
    VAR::remainArgs >> path;
    if (VS::IsWhiteString(path))
    {
        IO::INPUT("�ű�·��") >> path;
    }
    
    std::fstream scriptFile(path, std::ios::in);
    if (!scriptFile.good())
    {
        IO::ERROR("�ű�����ʧ�ܡ�");
        return;
    }
    
    std::string line;
    std::vector<std::string> cmd;
    std::function<void()> func;
    int pos;
    for (int i = 0; std::getline(scriptFile, line); i++)
    {
        IO::PRINT(i, "��", line);
        CTree::CommandSlice(line, cmd);
        func = VAR::admCmd.Retrieve(cmd, pos);
        
        VAR::remainArgs = std::stringstream();
        for (int i = pos; i < cmd.size(); i++)
        {
            VAR::remainArgs << cmd[i] << " ";
        }
        
        if (Execute(func) == false)
        {
            IO::ERROR("�ű���ֹ����", i, "�� ", line);
            return;
        }
    }
}

// �޸����롣
void ADM::Pswd()
{
    std::string oldpswd = IO::SECRT("������");
    
    if (VAR::currentUser.Authenticate(oldpswd) == false)
    {
        IO::ERROR("�������");
        return;
    }
    
    std::string newpswd = IO::SECRT("������");
    std::string cfmpswd = IO::SECRT("ȷ������");
    
    if (newpswd != cfmpswd)
    {
        IO::ERROR("���벻ƥ�䡣");
        return;
    }
    
    if (newpswd == SSP::Encrypt(""))
    {
        IO::MESSG("����δ�ı䡣");
        return;
    }
    
    User& user = DM::GetUser(VAR::currentUser.ID());
    user.ChangePassword(oldpswd, newpswd);
    VAR::currentUser = user;
    
    IO::MESSG("�����Ѹ��ġ�");
}

// �˳���¼��
void ADM::Logout()
{
    if (IO::CHECK(false, "ȷ���˳���") == false)
    {
        IO::MESSG("�˳���ȡ��");
        return;
    }
    IO::MESSG("�ɹ��˳����ټ� ", VAR::currentUser.Name(), "��");
    VAR::currentUser = UNKOWN_USER;
}

// �˳�����
void ADM::Exit()
{
    if (IO::CHECK(false, "ȷ���˳�����") == false)
    {
        IO::MESSG("�˳���ȡ��");
        return;
    }
    if (IO::CHECK(false, "�ٴ�ȷ�ϣ��˳�����") == false)
    {
        IO::MESSG("�˳���ȡ��");
        return;
    }
    IO::MESSG("������ֹ������");
    VAR::isRunning = false;
}

// �û����������Ϣ��
void ADM::USER::Help()
{
    IO::PRINT("�������");
    IO::PRINT("  help    - ��ʾ��������Ϣ");
    IO::PRINT("  view    - ��ʾ�����û�");
    IO::PRINT("  pswd    - ��������");
    IO::PRINT("  detail  - ��ʾ�û�ϸ��");
    IO::PRINT("  create  - �����û�");
    IO::PRINT("  delete  - ɾ���û�");
    IO::PRINT("���������");
    IO::PRINT("  detail -arg [�û� ID]");
    IO::PRINT("  create -arg [�û����� (stu/tch)] [�û� ID] [�û���]");
    IO::PRINT("  delete -arg [�û� ID]");
    IO::PRINT("ʾ����");
    IO::PRINT("  user view");
    IO::PRINT("  user detail -arg 20220001");
}

// ��ʾ�����û���
void ADM::USER::View()
{
    List<User> users = DM::AllUsers();
    for (int i = 0; i < users.Length(); i++)
    {
        IO::PRINT(ADM::USER::Peek(users[i].ID()));
    }
}

// �����û����롣
void ADM::USER::Pswd()
{
    std::string adminpswd = IO::SECRT("����Ա����");
    if (VAR::currentUser.Authenticate(adminpswd) == false)
    {
        IO::ERROR("�������");
        return;
    }
    
    ID_t uid = -1;
    IO::INPUT("�û� ID") >> uid;
    
    if (!DM::HasUser(uid))
    {
        IO::ERROR("��ѯ���� ID ", uid, "���û�������ʧ�ܡ�");
        return;
    }
    
    std::string newpswd = IO::SECRT("������");
    std::string cfmpswd = IO::SECRT("ȷ������");
    
    if (newpswd != cfmpswd)
    {
        IO::ERROR("���벻ƥ�䡣");
        return;
    }
    
    if (newpswd == SSP::Encrypt(""))
    {
        IO::MESSG("����δ�ı䡣");
        return;
    }
    
    User& user = DM::GetUser(uid);
    user.SetPassword(newpswd);
    IO::MESSG("�����Ѹ��ġ�");
}

// ��ʾ�û����顣
void ADM::USER::Detail()
{
    ID_t uid = -1;
    IO::INPUT("�û� ID") >> uid;
    if (!DM::HasUser(uid))
    {
        IO::ERROR("��ѯ���� ID  ", uid, "���û�������ʧ�ܡ�");
        return;
    }
    
    ADM::USER::Display(uid);
}

// �����û���
void ADM::USER::Create()
{
FLAG_FetchUserInfo:
    int type = -1;
    IO::INPUT("�û����� (ѧ�� 1, ��ʦ 2)") >> type;
    if (type != UserType::study && type != UserType::teach)
    {
        IO::ERROR("�Ƿ��û����ͣ�����ʧ�ܡ�");
        return;
    }
    
    ID_t uid = 0;
    IO::INPUT("�û� ID") >> uid;
    
    if (DM::HasUser(uid))
    {
        IO::ERROR("IDΪ ", uid, " ���û��Ѵ��ڣ�����ʧ�ܡ�");
        return;
    }
    
    std::string name = IO::CLINE("�û���");
    
    IO::PRINT("�û� ID��", uid);
    switch (type)
    {
    case UserType::study: IO::PRINT("�û�����: ѧ��"); break;
    case UserType::teach: IO::PRINT("�û�����: ��ʦ"); break;
    }
    IO::PRINT("�û�����", name);
    IO::PRINT("Ĭ��������ID��ͬ");
    if (IO::CHECK(true, "��ȷ��ȫ����Ϣ��") == false)
    {
        if (IO::CHECK(false, "����������Ϣ��") == false)
        {
            IO::MESSG("��������ʧ�ܡ�");
            return;
        }
        goto FLAG_FetchUserInfo;
    }
    
    switch (type)
    {
    case UserType::study:
        DM::AddStudent(Student(uid), name);
        break;
    case UserType::teach:
        DM::AddTeacher(Teacher(uid), name);
        break;
    }
    IO::MESSG("�ɹ������û���");
}

// ɾ���û���
void ADM::USER::Delete()
{
    ID_t uid = -1;
    IO::INPUT("�û� ID") >> uid;
    
    if (!DM::HasUser(uid))
    {
        IO::ERROR("��ѯ���� ID ", uid, "���û�������ʧ�ܡ�");
        return;
    }
    
    UserType type = DM::GetUser(uid).Type();
    User user = DM::GetUser(uid);
    
    Display(uid);
    if (IO::CHECK(false, "ȷ��ɾ���û���") == false)
    {
        IO::MESSG("ɾ����ȡ����");
        return;
    }
    
    switch (type)
    {
    case UserType::admin:
        IO::ERROR("����ɾ������Ա������ʧ�ܡ�");
        return;
    case UserType::study: {
        DM::RemoveStudent(uid);
        break; }
    case UserType::teach: {
        DM::RemoveTeacher(uid);
        break; }
    }
}

// ��ʾ�û����顣
// ���ڲ��������ú�����Ӧ����������������
void ADM::USER::Display(ID_t _uid)
{
    if (!DM::HasUser(_uid)) { return; }
    
    User user = DM::GetUser(_uid);
    IO::PRINT("�û� ID: ", user.ID());
    switch (user.Type())
    {
    case UserType::admin: IO::PRINT("�û����ͣ�����Ա"); break;
    case UserType::study: IO::PRINT("�û����ͣ�ѧ��"); break;
    case UserType::teach: IO::PRINT("�û����ͣ���ʦ"); break;
    }
    IO::PRINT("�û�����", user.Name());
    switch (user.Type())
    {
    case UserType::study: {
        Student stu = DM::GetStudent(_uid);
        
        IO::PRINT("��ѡ�γ̣�");
        List<ID_t> selected = stu.Selected();
        for (int i = 0; i < selected.Length(); i++)
        {
            IO::PRINT("  - ", ADM::COURSE::Peek(selected[i]));
        }
        break; }
    case UserType::teach: {
        Teacher tch = DM::GetTeacher(_uid);
        
        IO::PRINT("�����γ̣�");
        List<ID_t> teaching = tch.Taught();
        for (int i = 0; i < teaching.Length(); i++)
        {
            IO::PRINT("  - ", ADM::COURSE::Peek(teaching[i]));
        }
        break; }
    }
}

// ��ȡ�û���Ϣ��
// ���ڲ��������ú�����Ӧ����������������
std::string ADM::USER::Peek(ID_t _uid)
{
    if (!DM::HasUser(_uid)) { return ""; }
    
    User user = DM::GetUser(_uid);
    std::string info = "";
    switch (user.Type())
    {
    case UserType::admin: info += "[����Ա] "; break;
    case UserType::study: info += "[ѧ��] "; break;
    case UserType::teach: info += "[��ʦ] "; break;
    }
    info += std::to_string(user.ID()) + " ";
    info += "\"" + user.Name() + "\"";
    
    return info;
}

// ��ʾ�û����顣���Ӳ��������л�ȡ���ݣ�
void ADM::USER::DetailArg()
{
    ID_t uid = -1;
    VAR::remainArgs >> uid;
    
    if (!DM::HasUser(uid))
    {
        IO::ERROR("��ѯ���� ID ", uid, "���û�������ʧ�ܡ�");
        return;
    }
    
    Display(uid);
}

// �����û������Ӳ��������л�ȡ���ݣ�
void ADM::USER::CreateArg()
{
    std::string typestr = "";
    VAR::remainArgs >> typestr;
    if (typestr != "stu" && typestr != "tch" && typestr != "1" && typestr != "2")
    {
        IO::ERROR("�Ƿ��û����ͣ�����ʧ�ܡ�");
        return;
    }
    
    UserType type;
    if (typestr == "stu" || typestr == "1") { type = UserType::study; }
    else if (typestr == "tch" || typestr == "2") { type = UserType::teach; }
    
    ID_t uid = 0;
    VAR::remainArgs >> uid;
    
    if (DM::HasUser(uid))
    {
        IO::ERROR("IDΪ ", uid, " ���û��Ѵ��ڣ�����ʧ�ܡ�");
        return;
    }
    
    std::string name = "";
    VAR::remainArgs >> name;
    std::string tmp = "";
    while (VAR::remainArgs >> tmp) { name += " " + tmp; }
    
    switch (type)
    {
    case UserType::study:
        DM::AddStudent(Student(uid), name);
        break;
    case UserType::teach:
        DM::AddTeacher(Teacher(uid), name);
        break;
    }
    IO::MESSG("�ɹ������û���");
}

// ɾ���û������Ӳ��������л�ȡ���ݣ�
void ADM::USER::DeleteArg()
{
    ID_t uid = -1;
    VAR::remainArgs >> uid;
    
    if (!DM::HasUser(uid))
    {
        IO::ERROR("��ѯ���� ID ", uid, "���û�������ʧ�ܡ�");
        return;
    }
    
    UserType type = DM::GetUser(uid).Type();
    User user = DM::GetUser(uid);
    
    switch (type)
    {
    case UserType::admin:
        IO::ERROR("����ɾ������Ա������ʧ�ܡ�");
        return;
    case UserType::study:
        DM::RemoveStudent(uid);
        break;
    case UserType::teach:
        DM::RemoveTeacher(uid);
        break;
    }
    IO::MESSG("�û�ɾ���ɹ�");
}

// �γ̹��������Ϣ��
void ADM::COURSE::Help()
{
    IO::PRINT("�������");
    IO::PRINT("  help    - ��ʾ��������Ϣ");
    IO::PRINT("  view    - ��ʾ���пγ�");
    IO::PRINT("  detail  - ��ʾ�γ�ϸ��");
    IO::PRINT("  create  - �����γ�");
    IO::PRINT("  delete  - ɾ���γ�");
    IO::PRINT("  assign  - Ϊ�γ̷����ʦ");
    IO::PRINT("  enroll  - Ϊѧ��ע��γ�");
    IO::PRINT("  remove  - �ӿγ���ɾ��ѧ��");
    IO::PRINT("���������");
    IO::PRINT("  detail -arg [�γ� ID]");
    IO::PRINT("  create -arg [�γ� ID] [����] [��ʦ ID] [name]");
    IO::PRINT("  delete -arg [�γ� ID]");
    IO::PRINT("  assign -arg [�γ� ID] [��ʦ ID]");
    IO::PRINT("  enroll -arg [�γ� ID] [ѧ�� ID]");
    IO::PRINT("  remove -arg [�γ� ID] [ѧ�� ID]");
    IO::PRINT("ʾ����");
    IO::PRINT("  course view");
    IO::PRINT("  course detail -arg 123");
}

// �鿴���пγ̡�
void ADM::COURSE::View()
{
    List<Course> courses = DM::AllCourses();
    for (int i = 0; i < courses.Length(); i++)
    {
        IO::PRINT(ADM::COURSE::Peek(courses[i].ID()));
    }
}

// ��ʾ�γ����顣
void ADM::COURSE::Detail()
{
    ID_t cid = -1;
    IO::INPUT("�γ� ID") >> cid;
    if (!DM::HasCourse(cid))
    {
        IO::ERROR("��ѯ���� ID ", cid, "�Ŀγ̣�����ʧ�ܡ�");
        return;
    }
    
    Course course = DM::GetCourse(cid);
    Display(cid);
}

// �����γ̡�
void ADM::COURSE::Create()
{
FLAG_FetchCourseInfo:
    ID_t cid = 0;
    IO::INPUT("�γ� ID") >> cid;
    
    if (DM::HasCourse(cid))
    {
        IO::ERROR("IDΪ ", cid, " �Ŀγ��Ѵ��ڣ�����ʧ�ܡ�");
        return;
    }
    
    std::string name = IO::CLINE("�γ�����");
    Size_t capacity = 0;
    IO::INPUT("�γ�����") >> capacity;
    ID_t teacher = -1;
    IO::INPUT("���ν�ʦ ID") >> teacher;
    
    if (!DM::HasTeacher(teacher))
    {
        IO::ERROR("��ѯ���� ID ", teacher, "�Ľ�ʦ������ʧ�ܡ�");
        return;
    }
    
    IO::PRINT("�γ� ID��", cid);
    IO::PRINT("�γ����ƣ�", name);
    IO::PRINT("�γ�������", capacity);
    IO::PRINT("���ν�ʦ��", teacher);
    if (IO::CHECK(true, "��ȷ��ȫ����Ϣ��") == false)
    {
        if (IO::CHECK(false, "����������Ϣ��") == false)
        {
            IO::MESSG("��������ʧ�ܡ�");
            return;
        }
        goto FLAG_FetchCourseInfo;
    }
    
    DM::AddCourse(Course(cid, name, capacity, teacher));
}

// ɾ���γ̡�
void ADM::COURSE::Delete()
{
    ID_t cid = -1;
    IO::INPUT("�γ� ID") >> cid;
    
    if (!DM::HasCourse(cid))
    {
        IO::ERROR("��ѯ���� ID ", cid, "�Ŀγ̣�����ʧ�ܡ�");
        return;
    }
    
    Course course = DM::GetCourse(cid);
    
    Display(cid);
    if (IO::CHECK(false, "ȷ��ɾ���γ̣�") == false)
    {
        IO::MESSG("ɾ����ȡ����");
        return;
    }
    
    DM::RemoveCourse(cid);
    IO::MESSG("�γ�ɾ���ɹ���");
}

// Ϊ��ʦ����γ̡�
void ADM::COURSE::Assign()
{
    ID_t cid = -1;
    IO::INPUT("�γ� ID") >> cid;
    
    if (!DM::HasCourse(cid))
    {
        IO::ERROR("��ѯ���� ID ", cid, "�Ŀγ̣�����ʧ�ܡ�");
        return;
    }
    
    ADM::COURSE::Display(cid);
    
    Course course = DM::GetCourse(cid);
    
    ID_t teacher = -1;
    IO::INPUT("���ν�ʦ ID") >> teacher;
    
    if (!DM::HasTeacher(teacher))
    {
        IO::ERROR("��ѯ���� ID ", teacher, "�Ľ�ʦ������ʧ�ܡ�");
        return;
    }
    
    ADM::USER::Display(teacher);
    
    if (IO::CHECK(true, "ȷ�Ϸ��䣿") == false)
    {
        IO::MESSG("������ȡ����");
        return;
    }
    
    DM::Assign(teacher, cid);
    IO::MESSG("����ɹ���");
}

// Ϊѧ��ѡ��γ̡�
void ADM::COURSE::Enroll()
{
    ID_t cid = -1;
    IO::INPUT("�γ� ID") >> cid;
    
    if (!DM::HasCourse(cid))
    {
        IO::ERROR("��ѯ���� ID ", cid, "�Ŀγ̣�����ʧ�ܡ�");
        return;
    }
    
    ADM::COURSE::Display(cid);
    
    Course course = DM::GetCourse(cid);
    
    ID_t uid = -1;
    IO::INPUT("ѧ�� ID") >> uid;
    
    if (!DM::HasStudent(uid))
    {
        IO::ERROR("��ѯ���� ID ", uid, "��ѧ��������ʧ�ܡ�");
        return;
    }
    
    ADM::USER::Display(uid);
    
    if (IO::CHECK(true, "ȷ��ѡ�Σ�") == false)
    {
        IO::MESSG("ѡ����ȡ����");
        return;
    }
    
    DM::Enroll(uid, cid);
    IO::MESSG("ѡ�γɹ���");
}

// Ϊѧ����ѡ�γ̡�
void ADM::COURSE::Remove()
{
    ID_t cid = -1;
    IO::INPUT("�γ� ID") >> cid;
    
    if (!DM::HasCourse(cid))
    {
        IO::ERROR("��ѯ���� ID ", cid, "�Ŀγ̣�����ʧ�ܡ�");
        return;
    }
    
    ADM::COURSE::Display(cid);
    
    Course course = DM::GetCourse(cid);
    
    ID_t uid = -1;
    IO::INPUT("ѧ�� ID") >> uid;
    
    if (!DM::HasStudent(uid))
    {
        IO::ERROR("��ѯ���� ID ", uid, "��ѧ��������ʧ�ܡ�");
        return;
    }
    
    ADM::USER::Display(uid);
    
    if (IO::CHECK(true, "ȷ���˿Σ�") == false)
    {
        IO::MESSG("�˿���ȡ����");
        return;
    }
    
    DM::Remove(uid, cid);
    IO::MESSG("�˿γɹ���");
}

// ��ʾ�γ����顣
// ���ڲ��������ú�����Ӧ����������������
void ADM::COURSE::Display(ID_t _cid)
{
    if (!DM::HasCourse(_cid)) { return; }
    
    Course course = DM::GetCourse(_cid);
    IO::PRINT("�γ� ID: ", course.ID());
    IO::PRINT("�γ�����", course.Name());
    IO::PRINT("�γ�������", course.Capacity());
    IO::PRINT("��ѡ��ѧ������", course.Enrolled().Length());
    IO::PRINT("���ν�ʦ��", DM::GetUser(course.Teacher()).Name(), " ", course.Teacher());
}

// ��ȡ�γ���Ϣ��
// ���ڲ��������ú�����Ӧ����������������
std::string ADM::COURSE::Peek(ID_t _cid)
{
    if (!DM::HasCourse(_cid)) { return ""; }
    
    Course course = DM::GetCourse(_cid);
    std::string info = "";
    info += std::to_string(course.ID()) + " ";
    info += "\"" + course.Name() + "\"";
    info += " (" + std::to_string(course.Enrolled().Length()) + "/" + std::to_string(course.Capacity()) + ") ";
    info += DM::GetUser(course.Teacher()).Name();
    
    return info;
}

// ��ʾ�γ����顣���Ӳ��������л�ȡ���ݣ�
void ADM::COURSE::DetailArg()
{
    ID_t cid = -1;
    VAR::remainArgs >> cid;
    
    if (!DM::HasCourse(cid))
    {
        IO::ERROR("��ѯ���� ID ", cid, "�Ŀγ̣�����ʧ�ܡ�");
        return;
    }
    
    ADM::COURSE::Display(cid);
}

// �����γ̡����Ӳ��������л�ȡ���ݣ�
void ADM::COURSE::CreateArg()
{
    ID_t cid = 0;
    VAR::remainArgs >> cid;
    
    if (DM::HasCourse(cid))
    {
        IO::ERROR("IDΪ ", cid, " �Ŀγ��Ѵ��ڣ�����ʧ�ܡ�");
        return;
    }
    
    Size_t capacity = 0;
    VAR::remainArgs >> capacity;
    ID_t teacher = -1;
    VAR::remainArgs >> teacher;
    
    if (!DM::HasTeacher(teacher))
    {
        IO::ERROR("��ѯ���� ID ", teacher, "�Ľ�ʦ������ʧ�ܡ�");
        return;
    }
    
    std::string name = "";
    VAR::remainArgs >> name;
    std::string tmp = "";
    while (VAR::remainArgs >> tmp) { name += " " + tmp; }
    
    DM::AddCourse(Course(cid, name, capacity, teacher));
    IO::MESSG("�γ̴����ɹ���");
}

// ɾ���γ̡����Ӳ��������л�ȡ���ݣ�
void ADM::COURSE::DeleteArg()
{
    ID_t cid = -1;
    VAR::remainArgs >> cid;
    
    if (!DM::HasCourse(cid))
    {
        IO::ERROR("��ѯ���� ID ", cid, "�Ŀγ̣�����ʧ�ܡ�");
        return;
    }
    
    DM::RemoveCourse(cid);
    IO::MESSG("�γ�ɾ���ɹ���");
}

// Ϊ��ʦ����γ̡����Ӳ��������л�ȡ���ݣ�
void ADM::COURSE::AssignArg()
{
    ID_t cid = -1;
    VAR::remainArgs >> cid;
    
    if (!DM::HasCourse(cid))
    {
        IO::ERROR("��ѯ���� ID ", cid, "�Ŀγ̣�����ʧ�ܡ�");
        return;
    }
    
    ID_t teacher = -1;
    VAR::remainArgs >> teacher;
    
    if (!DM::HasTeacher(teacher))
    {
        IO::ERROR("��ѯ���� ID ", teacher, "�Ľ�ʦ������ʧ�ܡ�");
        return;
    }
    
    DM::Assign(teacher, cid);
    IO::MESSG("����ɹ���");
}

// Ϊѧ��ѡ��γ̡����Ӳ��������л�ȡ���ݣ�
void ADM::COURSE::EnrollArg()
{
    ID_t cid = -1;
    VAR::remainArgs >> cid;
    
    if (!DM::HasCourse(cid))
    {
        IO::ERROR("��ѯ���� ID ", cid, "�Ŀγ̣�����ʧ�ܡ�");
        return;
    }
    
    ID_t uid = -1;
    VAR::remainArgs >> uid;
    
    if (!DM::HasStudent(uid))
    {
        IO::ERROR("��ѯ���� ID ", uid, "��ѧ��������ʧ�ܡ�");
        return;
    }
    
    DM::Enroll(uid, cid);
    IO::MESSG("ѡ�γɹ���");
}

// Ϊѧ����ѡ�γ̡����Ӳ��������л�ȡ���ݣ�
void ADM::COURSE::RemoveArg()
{
    ID_t cid = -1;
    VAR::remainArgs >> cid;
    
    if (!DM::HasCourse(cid))
    {
        IO::ERROR("��ѯ���� ID ", cid, "�Ŀγ̣�����ʧ�ܡ�");
        return;
    }
    
    ID_t uid = -1;
    VAR::remainArgs >> uid;
    
    if (!DM::HasStudent(uid))
    {
        IO::ERROR("��ѯ���� ID ", uid, "��ѧ��������ʧ�ܡ�");
        return;
    }
    
    DM::Remove(uid, cid);
    IO::MESSG("�˿γɹ���");
}

#endif

/*

adminis
������ help
������ save
������ user
��   ������ help
��   ������ view
��   ������ detail
��   ������ create
��   ������ delete
������ course
��   ������ help
��   ������ view
��   ������ detail
��   ������ create
��   ������ delete
��   ������ assign
��   ������ enroll
������ logout
������ exit


*/