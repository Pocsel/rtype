#ifndef COMMON2__GAMEPLAYER_HPP__
#define COMMON2__GAMEPLAYER_HPP__

#include "BasicPlayer.hpp"

namespace Gmgp
{
    namespace Server
    {

        class IGame;
        class ITcpSocketProxy;

        template<typename E, typename G, typename PE>
            class Common2Player : public BasicPlayer
        {
        public:
            explicit Common2Player(uint16_t id,
                                   String const& nick,
                                   ITcpSocketProxy* socketProxy,
                                   IGame& game);
            ~Common2Player();

        private:
            PE* _player;
            int _score;
        };

    }
}

#endif

