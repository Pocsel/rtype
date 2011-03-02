
#include <cassert>

#include "Library.hpp"

using namespace Gmgp;

void Library::Load(void)
{
#ifdef WIN32
    this->_handle = ::LoadLibrary((this->GetPath() + ".dll").c_str());
#else
    this->_handle = ::dlopen((this->GetPath() + ".so").c_str(), RTLD_NOW);
#endif
}

bool Library::IsLoaded(void) const
{
    return this->_handle != 0;
}

void Library::Unload(void)
{
  if (this->_handle != 0)
  {
#ifdef WIN32
    ::FreeLibrary(this->_handle);
#else
    ::dlclose(this->_handle);
#endif
    this->_handle = 0;
  }
}

void* Library::Resolve(char const* name)
{
    assert(this->IsLoaded());

    if (this->IsLoaded() == false)
        throw std::runtime_error("Cannot Resolve when theres no library");

    void* func;
#ifdef WIN32
    func = ::GetProcAddress(this->_handle, name);
    if (func == 0)
        throw std::runtime_error((String("GetProcAddress error: ") + ::GetLastError()).c_str());
#else
    ::dlerror();
    func = ::dlsym(this->_handle, name);
    char const* err = ::dlerror();
    if (err != 0)
        throw std::runtime_error(err);
#endif
    return func;
}

