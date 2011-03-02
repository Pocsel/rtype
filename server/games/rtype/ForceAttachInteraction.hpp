#ifndef __FORCEATTACHINTERACTION_HPP__
#define __FORCEATTACHINTERACTION_HPP__

#include "AInteraction.hpp"
#include "GameEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        class ForceAttachInteraction : public AInteraction<GameEntity>
        {
        public:
            explicit ForceAttachInteraction(uint16_t playerId, bool isFront, GameEntity* entity);
            ~ForceAttachInteraction();

            bool Interact(GameEntity& entity);

            uint16_t GetPlayerId() const;
            void SetPos(Point const& p);
            Point const& GetPos() const;
            bool IsFront() const;

        public:
            Point position;
            Point speed;

        private:
            uint16_t _playerId;
            bool _isFront;
        };

    }
}

#endif

