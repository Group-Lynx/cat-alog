#ifndef VALID_STRING_H
#define VALID_STRING_H

#include <string>   // std::string
#include <sstream>  // std::stringstream

// Valid String - �ַ����Ϸ��Լ��
namespace VS
{
    bool IsWhiteString(std::string _str);
    bool IsNumber(std::string _str);
    int IsNumberSequence(std::string _str);
    std::string Trim(std::string _str);
};

// �ж��ַ����Ƿ�Ϊ�հ��ַ�����
bool VS::IsWhiteString(std::string _str)
{
    bool fullSpace = true;
    
    for (auto c : _str)
    {
        if (!isblank(c))
        {
            return false;
        }
    }
    return fullSpace;
}

// �ж��ַ����Ƿ�Ϊ���֡�
bool VS::IsNumber(std::string _str)
{
    if (IsWhiteString(_str)) { return false; }
    try
    {
        std::size_t pos = 0;
        std::stoll(_str, &pos);
        return pos == _str.length();
    }
    catch(const std::exception& e)
    {
        return false;
    }
}

// �ж��ַ����Ƿ�Ϊ�������С�
int VS::IsNumberSequence(std::string _str)
{
    if (IsWhiteString(_str)) { return false; }
    std::stringstream strss(_str);
    std::string tmp;
    int count = 0;
    while (strss >> tmp)
    {
        if (!IsNumber(tmp))
        {
            return false;
        }
        count++;
    }
    return count;
}

// ȥ���ַ����г��ȳ������İ��ַ�����ͷβ�հ׷���
std::string VS::Trim(std::string _str)
{
    std::string buffer;
    bool lastIsBlank = false;
    
    for (auto c : _str)
    {
        if (!isblank(c))
        {
            buffer += c;
            lastIsBlank = false;
            continue;
        }
        if (!lastIsBlank)
        {
            buffer += c;
        }
        lastIsBlank = true;
    }
    
    // ȥ��ͷβ�հ׷���
    if (isblank(buffer[0]))
    {
        buffer.erase(0, 1);
    }
    if (buffer.length() > 0 && isblank(buffer[buffer.length() - 1]))
    {
        buffer.erase(buffer.length() - 1, 1);
    }
    
    return buffer;
}

#endif