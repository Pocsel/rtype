
#ifndef ENDURANCEMAP1ENTITY_HPP_
# define ENDURANCEMAP1ENTITY_HPP_

#include "MapEntity.hpp"
#include "WallGeneratorEntity.hpp"
#include "MonsterGeneratorEntity.hpp"
#include "ForceEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        class EnduranceMap1Entity : public MapEntity
        {
        private:
            enum
            {
                BOSS_DELAY = 80,
                BOSS_SECOND_DELAY = 10,
                MOB_DELAY = 20,
                BONUS_DELAY = 30,
                BONUS_SHORT_DELAY = 10,
            };
        public:
            EnduranceMap1Entity(Game& game, size_t level);
            virtual ~EnduranceMap1Entity(void);

        private:
            void _IncreaseLevel(void);
            void _PrepareForBoss(void);
            void _SpawnBoss(void);
            void _SpawnBonus(void);

            void _SpawnForceBonus(void);
            void _SpawnSpeedBonus(void);
            void _SpawnForceDnaStyleBonus(void);
            void _SpawnForceBoingLaserBonus(void);
            void _SpawnForceFlameThrowerBonus(void);
            void _SpawnForceExplosiveBonus(void);

            WallGeneratorEntity _wallGenerator;
            std::vector<MonsterGeneratorEntity*> _monsterGenerators;
            std::vector<void (EnduranceMap1Entity::*)(void)> _bonuses;
            size_t _level;
        };

    }
}

#endif // !ENDURANCEMAP1ENTITY_HPP_
