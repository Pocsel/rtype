
#ifndef SHIPENTITY_HPP_
# define SHIPENTITY_HPP_

#include <vector>

#include "GameEntity.hpp"
#include "Item.hpp"
#include "ShipInteraction.hpp"
#include "TextEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        class EnemyDamageInteraction;
        class WallInteraction;
        class MonsterInteraction;
        class TriggerInteraction;
        class Game;
        class GamePlayer;

        class ShipEntity : public GameEntity
        {
            friend class Decorator;
        private:
            enum Direction
            {
                UP2 = 4,
                UP1 = 3,
                CENTER = 2,
                DOWN1 = 1,
                DOWN2 = 0,
            };

            enum
            {
                POWER_LOADING_TIME = 2,
                BASE_SPEED = 80,
                MAX_SPEED = 250,
                BONUS_SPEED = 30,
            };

        public:
            enum State
            {
                DEAD,
                SPAWNING,
                INDESTRUCTIBLE,
                ALIVE
            };

            explicit ShipEntity(Game& game, uint16_t playerId);
            ~ShipEntity(void);

            virtual void GenerateInteractions(float time);
            virtual void Run(float time);
            void InfoText(String const& text);

            // Interactions
            virtual bool Interact(EnemyDamageInteraction& interaction);
            virtual bool Interact(WallInteraction& interaction);
            virtual bool Interact(MonsterInteraction& interaction);
            virtual bool Interact(TriggerInteraction& interaction);
            virtual bool Interact(RepulseInteraction& interaction);
            virtual bool Interact(BonusInteraction& interaction);

            State const& GetState(void) const;
            Point GetPosition(void) const;

        private:
            void _Spawn();
            void _Explode();
            void _GetNextDirection(void);
            void _ShootMissile(float power);
            void _ShootMissile0(void);
            void _ShootMissile1(void);
            void _ShootMissile2(void);
            void _ShootMissile3(void);
            void _ShootMissile4(void);
            void _ShootMissile5(void);
            void _BonusForce(int type);
            void _BonusSpeed(int type);
            void _BonusForceUpgrade(int type);
            void _SetPowerSpriteEmpty(void);
            void _SetPowerSpriteLoading(void);
            void _SetPowerSpriteFull(void);
            void _UpdateScore(GamePlayer& p);

            Item _sprite;
            InteractionPtr _shipInteraction;
            InteractionPtr _forceFront;
            InteractionPtr _forceBack;
            InteractionPtr _forceControl;
            InteractionPtr _forceFire;
            InteractionPtr _repulse;
            int _direction;
            int _nextDirection;
            float _nextDirectionTime;

            State _state;
            float _spawnTime;

            Item _powerCadreSprite;
            Item _powerSprite;
            Item _powerLoadingSprite;
            Item _lives;
            bool _loadingPower;
            bool _loadedPower;
            float _powerLoadedTime;

            std::vector<void (ShipEntity::*)(void)> _missiles;
            std::vector<void (ShipEntity::*)(int)> _bonuses;

            float _speed;

            TextEntity<GameEntity, Game>* _score;
            float _nextAutoShoot;
        };

    }
}

#endif // !SHIPENTITY_HPP_
