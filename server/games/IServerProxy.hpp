
#ifndef ISERVERPROXY_HPP_
# define ISERVERPROXY_HPP_

#include <map>

#include "IService.hpp"
#include "AResourceInfo.hpp"
#include "String.hpp"

namespace Gmgp
{
    namespace Server
    {

        class IGame;

        class IServerProxy
        {
        public:
            virtual ~IServerProxy(void) {}

            virtual IService* GetService(void) const = 0;
            virtual void RegisterResource(AResourceInfo& infos) = 0;
            virtual std::map<uint16_t, IGame*> const& GetGameList(void) = 0;
        };

    }
}

#endif // !ISERVERPROXY_HPP_
