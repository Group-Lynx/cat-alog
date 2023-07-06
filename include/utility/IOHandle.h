#ifndef IO_HANDLE_H
#define IO_HANDLE_H

#include "../utility/Crypto.h"

#include <iostream>
#include <sstream>
#include <fstream>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

// ������ɫ ANSI ��
#define COLOR_RESET "\033[0;49m"
#define COLOR_MESSG "\033[96m"
#define COLOR_PROMP "\033[92m"
#define COLOR_ALERT "\033[33m"
#define COLOR_ERROR "\033[91m"
#define COLOR_PRINT "\033[0;49m"
#define COLOR_SHELL "\033[1;4;37m"
#define COLOR_DEBUG "\033[2m"

// == ���� == //

// Input Output Handle - �����������
class IO
{
public:
    IO() = delete;
    IO(const IO&) = delete;
    IO(IO&&) = delete;
    ~IO() = delete;
private:
    static bool colored;
    static char CaptureKey();
    static std::string SetColor(std::string _color);
public:
    static bool FlipColorStatus();
    template <typename... Args> static void MESSG(Args... _msgs);
    template <typename... Args> static void ALERT(Args... _msgs);
    template <typename... Args> static void ERROR(Args... _msgs);
    template <typename... Args> static void PRINT(Args... _msgs);
    template <typename... Args> static void DEBUG(Args... _msgs);
    template <typename... Args> static std::string CLINE(Args... _promt);
    template <typename... Args> static std::istringstream INPUT(Args... _promt);
    template <typename... Args> static std::string SECRT(Args... _promt);
    template <typename... Args> static bool CHECK(bool _default, Args... _promt);
    static std::string SHELL(std::string _name, char _sp = '>');
};

// == ���� == //

bool IO::colored = true;

// == ʵ�� == //

// ���񰴼���
char IO::CaptureKey()
{
#ifdef _WIN32
    return _getch();
#else
    struct termios oldSettings, newSettings;
    tcgetattr(STDIN_FILENO, &oldSettings);  // ��ȡ��ǰ����������
    newSettings = oldSettings;
    newSettings.c_lflag &= ~(ICANON | ECHO);  // ���ù淶ģʽ�ͻ���
    
    tcsetattr(STDIN_FILENO, TCSANOW, &newSettings);  // Ӧ��������
    
    char key;
    std::cin >> key;
    
    tcsetattr(STDIN_FILENO, TCSANOW, &oldSettings);  // ��ԭԭʼ����
    
    return key;
#endif
}

// ����������ɫ��
std::string IO::SetColor(std::string _color)
{
    if (colored)
    {
        return _color;
    }
    return "";
}

// ��ת��ɫ״̬��
bool IO::FlipColorStatus()
{
    colored = !colored;
    return colored;
}

// ��ӡ������Ϣ���������ָʾ����
template <typename... Args>
void IO::MESSG(Args... _msgs)
{
    std::cout << SetColor(COLOR_MESSG) << "[MESSG] ";
    ((std::cout << _msgs), ...);
    std::cout << SetColor(COLOR_RESET) << std::endl;
}

// ��ӡ������Ϣ���������ָʾ����
template <typename... Args>
void IO::ALERT(Args... _msgs)
{
    std::cout << SetColor(COLOR_ALERT) << "[ALERT] ";
    ((std::cout << _msgs), ...);
    std::cout << SetColor(COLOR_RESET) << std::endl;
}

// ��ӡ������Ϣ���������ָʾ����
template <typename... Args>
void IO::ERROR(Args... _msgs)
{
    std::cout << SetColor(COLOR_ERROR) << "[ERROR] ";
    ((std::cout << _msgs), ...);
    std::cout << SetColor(COLOR_RESET) << std::endl;
}

// ��ӡ���ݡ�
template <typename... Args>
void IO::PRINT(Args... _msgs)
{
    std::cout << SetColor(COLOR_PRINT);
    ((std::cout << _msgs), ...);
    std::cout << SetColor(COLOR_RESET) << std::endl;
}

// ��ӡ������Ϣ���������ָʾ����
template <typename... Args>
void IO::DEBUG(Args... _msgs)
{
    std::cout << SetColor(COLOR_DEBUG) << "[DEBUG] ";
    ((std::cout << _msgs), ...);
    std::cout << SetColor(COLOR_RESET) << std::endl;
}

// ��ȡһ�����ݡ���������ָʾ����
template <typename... Args>
std::string IO::CLINE(Args... _promt)
{
    std::cout << SetColor(COLOR_PROMP) << "[INPUT] ";
    ((std::cout << _promt), ...);
    std::cout << ": " << SetColor(COLOR_RESET);
    
    std::string input;
    std::getline(std::cin, input);
    
    return input;
}

// ���Ķ�ȡ���ݡ���������ָʾ����
template <typename... Args>
std::istringstream IO::INPUT(Args... _promt)
{
    std::cout << SetColor(COLOR_PROMP) << "[INPUT] ";
    ((std::cout << _promt), ...);
    std::cout << ": " << SetColor(COLOR_RESET);
    
    std::string input;
    std::getline(std::cin, input);
    
    return std::istringstream(input);
}

// ���Ķ�ȡ���ݣ����ؼ��ܺ���ı�����������ָʾ����
template <typename... Args>
std::string IO::SECRT(Args... _promt)
{
#ifdef _WIN32
    std::cout << SetColor(COLOR_PROMP) << "[SECRT] ";
    ((std::cout << _promt), ...);
    std::cout << ": " << SetColor(COLOR_RESET);
    
    char tmp;
    std::string input;
    while ((tmp = CaptureKey()) != '\n' && tmp != '\r')
    {
        if (tmp == '\b' && !input.empty())
        {
            input.pop_back();
            std::cout << "\b \b";
            continue;
        }
        input.push_back(tmp);
        std::cout << '*';
    }
    std::cout << std::endl;
    
    return SSP::Encrypt(input);
#else
    std::string prompt = SetColor(COLOR_PROMP) + std::string("[SECRT] ");
    ((prompt += _promt), ...);
    prompt += std::string(": ") + SetColor(COLOR_RESET);
    
    std::string input(getpass(prompt.c_str()));
    
    return SSP::Encrypt(input);
#endif
}

// ��ѡһѡ�񡣰�������ָʾ����
template <typename... Args>
bool IO::CHECK(bool _default, Args... _promt)
{
    std::cout << SetColor(COLOR_PROMP) << "[CHECK] ";
    ((std::cout << _promt), ...);
    
    if (_default) { std::cout << " (y)/n: "; }
    else { std::cout << " y/(n): "; }
    std::cout << SetColor(COLOR_RESET);
    
    bool option = _default;
    char input = CaptureKey();
    switch (tolower(input))
    {
    case 'y': option = true; break;
    case 'n': option = false; break;
    default: break;
    }
    std::cout << (option ? 'y' : 'n') << std::endl;
    
    return option;
}

// ��ʾ�����н���ָʾ��
std::string IO::SHELL(std::string _name, char _sp)
{
    std::cout << SetColor(COLOR_SHELL) << _name << SetColor(COLOR_RESET) << _sp << " ";
    std::string cmd;
    std::getline(std::cin, cmd);
    return cmd;
}

#endif