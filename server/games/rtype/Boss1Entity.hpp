
#ifndef BOSS1ENTITY_HPP_
# define BOSS1ENTITY_HPP_

#include <vector>

#include "GameEntity.hpp"
#include "Item.hpp"
#include "Resources.hpp"
#include "String.hpp"

namespace Gmgp
{
    namespace Server
    {

        class Game;
        class Boss1Node;

        class Boss1Entity : public GameEntity
        {
            friend class Decorator;
            friend class Boss1Node;
        private:
            enum
            {
                LIFE = 50,
                BODY_WIDTH = 154,
                BODY_HEIGHT = 204,
                TENIA_X_OFFSET = 72,
                TENIA_Y_OFFSET = 94,
                TENIA_WIDTH = 32,
                TENIA_HEIGHT = 32,
                NB_NODES = 12,
                NODE_WIDTH = 10,
                TAIL_X_OFFSET = 63,
                TAIL_Y_OFFSET = 186,
                START_X_OFFSET = 100,
                MOUTH_X_OFFSET = 28,
                MOUTH_Y_OFFSET = 72,
                DEATH_TIME = 5,
            };

            enum
            {
                CLOSED,
                OPENING,
                CLOSING,
                OPENED,
                DEAD,
            };

        public:
            explicit Boss1Entity(Game& game, int level = 0);
            virtual ~Boss1Entity(void);

            virtual void GenerateInteractions(float time);
            virtual void Run(float time);

            // Interactions
            virtual bool Interact(FriendlyDamageInteraction& interaction);
            virtual bool Interact(ShipInteraction& interaction);

        private:
            void _Shoot(float time);
            void _MoveQueue(float time);
            bool _Damage(int damage, uint16_t playerId);
            void _Die(void);
            void _RandomExplosion(void);
            void _CallNextMap(void);

            Item _body;
            Item _tenia;
            Item _life;
            Item _lifeCadre;
            bool _blink;
            float _stopBlinkTime;

            InteractionPtr _bodyHead;
            InteractionPtr _bodyTop;
            InteractionPtr _bodyDown;
            InteractionPtr _bodyQueue;
            size_t _maxLife;
            InteractionPtr _teniaInteraction;

            std::vector<Boss1Node*> _nodes;

            bool _inPosition;
            uint16_t _lastHit;

            int _state;
            float _openTime;

            float _shootTime;

            float _deathTime;
            float _nextDeathEvent;
            bool _middleEvent;

            std::vector<int> _explosions;

            int _level;
        };

    }
}


#endif // !BOSS1ENTITY_HPP_
