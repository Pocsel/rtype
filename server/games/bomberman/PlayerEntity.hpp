#ifndef __PLAYERENTITY_HPP__
#define __PLAYERENTITY_HPP__

#include "Entity.hpp"
#include "Item.hpp"

namespace Gmgp
{
    namespace Server
    {

        class Player;
        class BombInteraction;
        class IGame;

        class PlayerEntity :
            public Entity
        {
        private:
            enum
            {
                SPEED = 70,
                Y_OFFSET = 4,
            };

            enum
            {
                NONE = 0,
                UP,
                DOWN,
                LEFT,
                RIGHT,
            };

            public:
                explicit PlayerEntity(Game& game, uint16_t playerId, String const& nick);
                ~PlayerEntity();
                virtual void Run(float time);
                int GetColorId() const;
                void Spawn(int x, int y);
                bool IsAlive() const;

                virtual bool Interact(BombInteraction& interaction);
                virtual bool Interact(BonusInteraction& interaction);

            private:
                void _Bombing(Player& player);
                void _Movement(Player& player);
                void _Taunt(Player& player);
                void _Die(uint16_t killerId);

                int _colorId;
                Item _sprite;
                int _direction;
                Point _target;
                int _power;
                int _nbBombs;
                bool _alive;
                bool _justSpawned;
        };

    }
}

#endif

