
#ifndef MANAGERENTITY_HPP_
# define MANAGERENTITY_HPP_

#include "Common2ManagerEntity.hpp"
#include "BallEntity.hpp"
#include "Entity.hpp"

namespace Gmgp
{
    namespace Server
    {

        class Game;
        class PlayerEntity;

        class ManagerEntity : public Common2ManagerEntity<Entity, Game, PlayerEntity>
        {
        public:
            enum
            {
                BAR_WIDTH = 16,
                BAR_HEIGHT = 80,
            };
        public:
            explicit ManagerEntity(Game& game);
            virtual ~ManagerEntity();

        protected:
            virtual int _GetIconId() const;
            virtual int _GetBgId() const;

            virtual void _SpawnMap();
            virtual void _DestroyMap();

        private:
            BallEntity _ball;
            Item _bar;
        };

    }
}

#endif // !MANAGERENTITY_HPP_
