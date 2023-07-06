#ifndef FILE_HANDLE_H
#define FILE_HANDLE_H

#include "../utility/Crypto.h"

#include <fstream>
#include <string>

// File Handle - �ļ�����
class FH
{
public:
    FH() = delete;
    FH(const FH&) = delete;
    FH(FH&&) = delete;
    ~FH() = delete;
public:
    template <typename... Args> static std::string CombinePath(Args... _paths);
    static bool Validate(std::string _path, std::string _code);
    static std::string Signature(std::string _path);
};

// �ϲ�·����
template <typename... Args>
std::string FH::CombinePath(Args... _paths)
{
    std::string path;
    ((path += _paths), ...);
    return path;
}

// ��֤�ļ���
bool FH::Validate(std::string _path, std::string _code)
{
    std::ifstream file(_path);
    if (!file.good()) { return false; }
    
    return Signature(_path) == _code;
}

// ��ȡ�ļ�ʶ���롣
std::string FH::Signature(std::string _path)
{
    std::ifstream file(_path);
    if (!file.good()) { return SSP::Encrypt(""); }
    
    std::string content;
    std::string line;
    while (!file.eof())
    {
        std::getline(file, line);
        content += line + "\n";
    }
    
    return SSP::Encrypt(content);
}

#endif