#ifndef __IGAME_HPP__
#define __IGAME_HPP__

#include "String.hpp"
#include "IServerProxy.hpp"

#ifdef _WIN32
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif /* _WIN32 */

namespace Gmgp
{
    namespace Server
    {

        class IGame
        {
            public:
                virtual ~IGame() {}

                virtual String const& GetName(void) const = 0;
                virtual bool Initialize(IServerProxy& serverProxy) = 0;
                virtual void AddPlayer(uint16_t playerId, String const& nick, ITcpSocketProxy* socket) = 0;
                virtual IService& GetService(void) = 0;
                virtual void Run(void) = 0;
                virtual void Stop(void) = 0;

                //new
                virtual void RemovePlayer(uint16_t playerId) = 0;
        };

    }
}

#endif

