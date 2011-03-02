
#include <string>
#include <sstream>
#include <iostream>

#include "Console.hpp"
#include "Function.hpp"

namespace Gmgp
{
    namespace Server
    {

        Console::Console()
        {
            this->bind("help", *this, &Console::help, "print this help");
        }

        std::string Console::sendLine(std::string const& line)
        {
            std::stringstream ss(line);
            std::string cmd;
            ss >> cmd;
            std::map<std::string, Functor>::iterator it = this->_commands.find(cmd);
            if (it != this->_commands.end())
            {
                std::string params;
                std::getline(ss, params);
                try
                {
                    return it->second(params);
                }
                catch (std::exception const& e)
                {
                    return std::string("Exception: ") + e.what();
                }
            }
            return "Command not found: " + cmd;
        }

        std::string Console::help() const
        {
            std::string res = "List of available commands:";
            std::map<std::string, Functor>::const_iterator it = this->_commands.begin();
            for (; it != this->_commands.end(); ++it)
            {
                std::map<std::string, std::string>::const_iterator hit = this->_help.find(it->first);
                if (hit->second.size() > 0)
                    res += "\n  - " + it->first + ": " + hit->second;
                else
                    res += "\n  - " + it->first;
            }
            return res;
        }

    }
}
