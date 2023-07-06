#ifndef COMMAND_TREE_H
#define COMMAND_TREE_H

#include <vector>      // std::vector<>
#include <string>      // std::string
#include <functional>  // std::function<>
#include <memory>      // std::unique_ptr<>

// == 声明 == //

// Command Tree - 命令树
class CTree
{
    // 静域 //
public:
    static void CommandSlice(std::string _input, std::vector<std::string>& _cmd);
    // 个域 //
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

// == 定义 == //

// 将命令切分成小段，使其能被命令树解释。
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

// == 实现 == //

// 构建一棵命令树并为其绑定函数。
CTree::CTree(std::string _pattern, std::function<void()> _func)
{
    function = _func;
    pattern = _pattern;
}

// 生长一个命令子树
void CTree::Grow(std::unique_ptr<CTree> _child)
{
    children.push_back(std::move(_child));
}

// 解释命令，得到被解释为的函数。
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

// 解释命令，得到被解释为的函数，同时获取余下的命令。
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