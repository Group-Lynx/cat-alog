#ifndef COMMAND_TREE_H
#define COMMAND_TREE_H

#include <vector>      // std::vector<>
#include <string>      // std::string
#include <functional>  // std::function<>
#include <memory>      // std::unique_ptr<>

// == ���� == //

// Command Tree - ������
class CTree
{
    // ���� //
public:
    static void CommandSlice(std::string _input, std::vector<std::string>& _cmd);
    // ���� //
private:
    std::function<void()> function;
    std::string pattern;
    std::vector<std::unique_ptr<CTree>> children;
public:
    CTree(std::string _pattern, std::function<void()> _func);
    
    void Grow(std::unique_ptr<CTree> _child);
    std::function<void()> Retrieve(std::vector<std::string> _patterns);
    std::function<void()> Retrieve(std::vector<std::string> _patterns, int& _pos);
};

// == ���� == //

// �������зֳ�С�Σ�ʹ���ܱ����������͡�
void CTree::CommandSlice(std::string _input, std::vector<std::string>& _cmd)
{
    _cmd.clear();
    size_t pos = 0;
    while ((pos = _input.find(' ')) != std::string::npos)
    {
        _cmd.push_back(_input.substr(0, pos));
        _input.erase(0, pos + 1);
    }
    _cmd.push_back(_input);
}

// == ʵ�� == //

// ����һ����������Ϊ��󶨺�����
CTree::CTree(std::string _pattern, std::function<void()> _func)
{
    function = _func;
    pattern = _pattern;
}

// ����һ����������
void CTree::Grow(std::unique_ptr<CTree> _child)
{
    children.push_back(std::move(_child));
}

// ��������õ�������Ϊ�ĺ�����
std::function<void()> CTree::Retrieve(std::vector<std::string> _patterns)
{
    CTree* current = this;
    bool found = false;
    
    for (int i = 0; i < _patterns.size(); i++)
    {
        found = false;
        for (auto& child : current->children)
        {
            if (child->pattern == _patterns[i])
            {
                found = true;
                current = child.get();
                break;
            }
        }
        
        if (!found) { break; }
    }
    
    return current->function;
}

// ��������õ�������Ϊ�ĺ�����ͬʱ��ȡ���µ����
std::function<void()> CTree::Retrieve(std::vector<std::string> _patterns, int& _pos)
{
    CTree* current = this;
    bool found = false;
    
    for (_pos = 0; _pos < _patterns.size(); _pos++)
    {
        found = false;
        for (auto& child : current->children)
        {
            if (child->pattern == _patterns[_pos])
            {
                found = true;
                current = child.get();
                break;
            }
        }
        
        if (!found) { break; }
    }
    
    return current->function;
}

#endif