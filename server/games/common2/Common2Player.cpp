#include "Common2Player.hpp"
#include "Common2PlayerEntity.hpp"
#include "ITcpSocketProxy.hpp"
#include "Log.hpp"

namespace Gmgp
{
    namespace Server
    {

        template<typename E, typename G, typename PE>
            Common2Player<E, G, PE>::Common2Player(uint16_t id,
                                         String const& nick,
                                         ITcpSocketProxy* socketProxy,
                                         IGame& game) :
                BasicPlayer(id, nick, socketProxy, game)
        {
            Log::I(this->GetNick() + " entered a Common2 game.");
            this->_player = new PE(reinterpret_cast<G&>(game), id, nick);
        }

        template<typename E, typename G, typename PE>
            Common2Player<E, G, PE>::~Common2Player()
            {
                Log::I(this->GetNick() + " left a Common2 game.");
                delete this->_player;
            }

    }
}

