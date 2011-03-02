#ifndef __LOG_HPP__
#define __LOG_HPP__

#include "String.hpp"

namespace Gmgp
{

    class Log
    {
    public:
#ifdef DEBUG
        static void D(String const& message)
        {
            std::cout << "Debug   | " + message + "\n";
        }
#else
        static void D(String const&)
        {
        }
#endif
        static void I(String const& message)
        {
            std::cout << "Info    | " + message + "\n";
        }
        static void W(String const& message)
        {
            std::cout << "Warning | " + message + "\n";
        }
        static void E(String const& message)
        {
            std::cerr << "Error   | " + message + "\n";
        }
    };

}

#endif

