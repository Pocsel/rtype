
#ifndef __LIBRARY_HPP__
# define __LIBRARY_HPP__

# ifdef WIN32
#  include <direct.h>
#  include <windows.h>
# else
#  include <sys/types.h>
#  include <dlfcn.h>
# endif

# include "AbstractResource.hpp"

namespace Gmgp
{
  class Library : public AbstractResource<uint16_t>
  {
    private:
# ifdef WIN32
      typedef HINSTANCE handle_t;
# else
      typedef void* handle_t;
# endif

    private:
      handle_t _handle;

    public:
      Library(std::string const& path, uint16_t id) :
        AbstractResource<uint16_t>(path, id), _handle(0)
      {
      }

      virtual void Load(void);
      virtual bool IsLoaded(void) const;
      virtual void Unload(void);
      void* Resolve(char const* name);
      template<typename Cast>
      Cast Resolve(char const* name)
      {
        return reinterpret_cast<Cast>(this->Resolve(name));
      }
  };
}

#endif /* !__LIBRARY_HPP__ */

