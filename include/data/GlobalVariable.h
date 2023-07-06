#ifndef GLOBAL_VARIABLE_H
#define GLOBAL_VARIABLE_H

#include "../object/User.h"

#include "../command/CommandTree.h"

#include "../utility/IOHandle.h"

namespace STU { void None(); }
namespace TCH { void None(); }
namespace ADM { void None(); }
namespace CMD { void None(); }

// Global variables - 全局变量
class VAR
{
public:
    VAR() = delete;
    VAR(const VAR&) = delete;
    VAR(VAR&&) = delete;
    ~VAR() = delete;
public:
    static CTree stuCmd;
    static CTree tchCmd;
    static CTree admCmd;
    static CTree gnlCmd;
    
    static User currentUser;
    
    static bool isRunning;
    
    static std::stringstream remainArgs;
};

CTree VAR::stuCmd("student", STU::None);
CTree VAR::tchCmd("teacher", TCH::None);
CTree VAR::admCmd("adminis", ADM::None);
CTree VAR::gnlCmd("deneral", CMD::None);

User VAR::currentUser = UNKOWN_USER;
bool VAR::isRunning = true;
std::stringstream VAR::remainArgs = std::stringstream();

#endif