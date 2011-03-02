
#ifndef DLHANDLER_HPP_
# define DLHANDLER_HPP_

#include "String.hpp"

#ifdef _WIN32
#include <Windows.h>
typedef FARPROC DLSym;
typedef HMODULE DLHandle;
#else
#include <dlfcn.h>
typedef void* DLSym;
typedef void* DLHandle;
#endif

namespace Gmgp
{
    namespace Server
    {

        class DLHandler
        {
        public:
            DLHandler(String const & filename);
            ~DLHandler(void);
            DLSym GetDLSym(String const & symname);

        private:
            DLHandle _dl;
        };

    }
}

#endif // !DLHANDLER_HPP_
