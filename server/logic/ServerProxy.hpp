
#ifndef SERVERPROXY_HPP_
# define SERVERPROXY_HPP_

#include "IServerProxy.hpp"
#include "Mutex.hpp"

namespace Gmgp
{
    namespace Server
    {

        class Server;

        class ServerProxy : public IServerProxy
        {
        public:
            ServerProxy(Server& server);
            ~ServerProxy(void);

            virtual IService* GetService(void) const;
            virtual void RegisterResource(AResourceInfo& infos);
            virtual std::map<uint16_t, IGame*> const& GetGameList(void);

        private:
            Server& _server;
        };

    }
}

#endif // !SERVERPROXY_HPP_
