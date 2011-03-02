#ifndef __FORCECONTROLINTERACTION_HPP__
#define __FORCECONTROLINTERACTION_HPP__

#include "AInteraction.hpp"
#include "GameEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        class ForceControlInteraction : public AInteraction<GameEntity>
        {
        public:
            explicit ForceControlInteraction(uint16_t playerId, GameEntity* entity);
            ~ForceControlInteraction();

            bool Interact(GameEntity& entity);

            void SetPos(Point const& p);
            Point const& GetPos() const;
            uint16_t GetPlayerId() const;

        private:
            uint16_t _playerId;
            Point _pos;
        };

    }
}

#endif

