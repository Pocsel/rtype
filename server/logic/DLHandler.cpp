
#include <iostream>
#include <stdexcept>

#include "DLHandler.hpp"
#include "Log.hpp"

namespace Gmgp
{
    namespace Server
    {

#ifdef _WIN32 //windows

        DLHandler::DLHandler(String const & filename)
        {
            this->_dl = LoadLibrary(filename.c_str());
            if (this->_dl == 0)
                throw std::runtime_error("LoadLibrary failure : could not open " + filename);
        }

        DLHandler::~DLHandler(void)
        {
            if (FreeLibrary(this->_dl) == 0)
                Log::W("Warning : FreeLibrary failure");
        }

        DLSym DLHandler::GetDLSym(String const & symName)
        {
            DLSym sym = GetProcAddress(this->_dl, symName.c_str());
            if (sym == 0)
                throw std::runtime_error("error : symbol " + symName + " not present");
            return sym;
        }

#else //unix

        DLHandler::DLHandler(String const & filename)
        {
            String realFilename;
            if (filename[0] != '/' && filename[0] != '.')
                realFilename = "./" + filename;
            else
                realFilename = filename;
            realFilename += ".so";
            this->_dl = dlopen(realFilename.c_str(), RTLD_NOW);
            if (this->_dl == 0)
                throw std::runtime_error(String("dlopen failure(could not open " + realFilename + "): " + dlerror()).c_str());
        }

        DLHandler::~DLHandler(void)
        {
            if (dlclose(this->_dl) != 0)
                Log::W("Warning : dlclose failure");
        }

        DLSym DLHandler::GetDLSym(String const & symName)
        {
            DLSym sym = dlsym(this->_dl, symName.c_str());
            if (sym == 0)
                throw std::runtime_error("error : symbol " + symName + " not present");
            return sym;
        }
#endif

    }
}
