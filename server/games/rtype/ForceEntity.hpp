#ifndef __FORCEENTITY_HPP__
#define __FORCEENTITY_HPP__

#include <list>
#include <vector>

#include "GameEntity.hpp"
#include "Item.hpp"
#include "BonusInteraction.hpp"

namespace Gmgp
{
    namespace Server
    {

        class Game;

        class ForceEntity : public GameEntity
        {
            public:
                explicit ForceEntity(Game& game);
                ~ForceEntity(void);
                virtual void GenerateInteractions(float time);
                virtual void Run(float time);
                virtual bool Interact(ForceAttachInteraction& i);
                virtual bool Interact(ForceControlInteraction& i);
                virtual bool Interact(ForceFireInteraction& i);
                virtual bool Interact(ForceUpgradeInteraction& i);
                virtual bool Interact(ForceDowngradeInteraction& i);

            private:
                enum Params
                {
                    SPEED = 80,
                    FREE_SPEED = 30,
                    LAUNCH_SPEED = 250,
                    PRECISION = 5,
                };

                enum Weapon
                {
                    LEVEL0 = BonusInteraction::FORCE_DNA_STYLE - 2,
                    LEVEL1 = BonusInteraction::FORCE_DNA_STYLE - 1,
                    DNA_STYLE = BonusInteraction::FORCE_DNA_STYLE,
                    BOING_LASER = BonusInteraction::FORCE_BOING_LASER,
                    FLAME_THROWER = BonusInteraction::FORCE_FLAME_THROWER,
                    EXPLOSIVE = BonusInteraction::FORCE_EXPLOSIVE,
                };

                enum State
                {
                    ATTACHED_FRONT,
                    ATTACHED_BACK,
                    FREE_FRONT,
                    FREE_BACK,
                    LAUNCHED_FRONT,
                    LAUNCHED_BACK,
                    TARGET
                };

                bool _MoveToTarget();
                bool _IsNearX(float x) const;
                bool _IsNearY(float y) const;
                void _NewPosition();
                void _ChooseNearestTarget();
                void _InitShoots(void);
                float _ShootNothing(void);
                float _ShootLevel0Detached(void);
                float _ShootLevel1AttachedFront(void);
                float _ShootLevel1AttachedBack(void);
                float _ShootLevel1Detached(void);
                float _ShootLevel2Detached(void);
                float _ShootDnaStyleFront(void);
                float _ShootDnaStyleBack(void);
                float _ShootBoingLaserFront(void);
                float _ShootBoingLaserBack(void);
                float _ShootFlameThrowerFront(void);
                float _ShootFlameThrowerBack(void);
                float _ShootExplosiveFront(void);
                float _ShootExplosiveBack(void);
                InteractionPtr _damage;
                InteractionPtr _shield;
                uint16_t _playerId;
                Item _sprite;
                int _state;
                Point _target;
                float _speed;
                std::list<Point> _attracts;
                float _nextFireTime;
                std::vector<float (ForceEntity::*)(void)> _attachedFrontShoots;
                std::vector<float (ForceEntity::*)(void)> _attachedBackShoots;
                std::vector<float (ForceEntity::*)(void)> _detachedShoots;
                Weapon _weapon;
        };

    }
}

#endif

