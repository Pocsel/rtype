
#include "ServerProxy.hpp"
#include "Server.hpp"
#include "Mutex.hpp"
#include "ScopeLock.hpp"

namespace Gmgp
{
    namespace Server
    {

        ServerProxy::ServerProxy(Server& server)
            : _server(server)
        {
        }

        ServerProxy::~ServerProxy(void)
        {
        }

        IService* ServerProxy::GetService(void) const
        {
            return this->_server.GetService();
        }

        void ServerProxy::RegisterResource(AResourceInfo& infos)
        {
            this->_server.RegisterResource(infos);
        }

        std::map<uint16_t, IGame*> const& ServerProxy::GetGameList(void)
        {
            return this->_server.GetGameList();
        }

    }
}
