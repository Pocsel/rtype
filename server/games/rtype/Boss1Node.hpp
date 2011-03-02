
#ifndef BOSS1NODE_HPP_
# define BOSS1NODE_HPP_

#include <vector>

#include "GameEntity.hpp"
#include "Item.hpp"

namespace Gmgp
{
    namespace Server
    {

        class Game;
        class Boss1Entity;

        class Boss1Node
        {
            friend class Decorator;
            friend class Boss1Entity;
        public:
            explicit Boss1Node(Game& game, int pos);
            ~Boss1Node(void);
            void StopX(void);
            void GenerateInteraction(void);
            void Move(float time);

        private:
            void _Shoot(void);
            void _ShootDown(void);
            void _ShootDownLeft(void);
            void _ShootLeft(void);
            void _ShootUpLeft(void);
            void _ShootUp(void);

            Game& _game;
            Item _node;
            GameEntity::InteractionPtr _wallInteraction;
            float _moveTime;
            int _pos;
            bool _started;
            float _shootTime;
            int _dir;
            std::vector<void (Boss1Node::*)(void)> _shoots;
        };

    }
}

#endif // !BOSS1NODE_HPP_
