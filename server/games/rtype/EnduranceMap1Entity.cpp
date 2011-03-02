
#include "EnduranceMap1Entity.hpp"
#include "functor.hpp"
#include "Game.hpp"
#include "ForceEntity.hpp"
#include "BonusEntity.hpp"
#include "BonusInteraction.hpp"
#include "Resources.hpp"
#include "Boss1Entity.hpp"
#include "ForceEntity.hpp"
#include "BonusCarrierMobEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        EnduranceMap1Entity::EnduranceMap1Entity(Game& game, size_t level)
            : MapEntity(game), _wallGenerator(game, game.R() * 2, level / 2), _level(level)
        {
            this->_RegisterEvent(this->_game.GetElapsedTime() + BOSS_DELAY,
                                 b00st::bind(&EnduranceMap1Entity::_PrepareForBoss, *this));
            this->_RegisterEvent(this->_game.GetElapsedTime() + MOB_DELAY,
                                 b00st::bind(&EnduranceMap1Entity::_IncreaseLevel, *this));
            this->_RegisterEvent(this->_game.GetElapsedTime() + BONUS_DELAY,
                                 b00st::bind(&EnduranceMap1Entity::_SpawnBonus, *this));

            this->_bonuses.push_back(&EnduranceMap1Entity::_SpawnSpeedBonus);
            this->_bonuses.push_back(&EnduranceMap1Entity::_SpawnForceDnaStyleBonus);
            this->_bonuses.push_back(&EnduranceMap1Entity::_SpawnForceBoingLaserBonus);
            this->_bonuses.push_back(&EnduranceMap1Entity::_SpawnForceFlameThrowerBonus);
            this->_bonuses.push_back(&EnduranceMap1Entity::_SpawnForceExplosiveBonus);
        }

        EnduranceMap1Entity::~EnduranceMap1Entity(void)
        {
            for (std::vector<MonsterGeneratorEntity*>::iterator it = this->_monsterGenerators.begin(),
                 ite = this->_monsterGenerators.end() ; it != ite ; ++it)
                delete *it;
            this->_monsterGenerators.clear();
        }

        void EnduranceMap1Entity::_SpawnBonus(void)
        {
            size_t forces = this->_game.GetForces().size();
            size_t players = this->_game.GetListOfPlayers().size() * (this->_level > 4 ? 2 : 1);
            if (forces < players)
            {
                this->_SpawnForceBonus();
                if (players - forces > 1)
                    this->_RegisterEvent(this->_game.GetElapsedTime() + BONUS_SHORT_DELAY,
                                         b00st::bind(&EnduranceMap1Entity::_SpawnBonus, *this));
                else
                    this->_RegisterEvent(this->_game.GetElapsedTime() + BONUS_DELAY,
                                         b00st::bind(&EnduranceMap1Entity::_SpawnBonus, *this));
            }
            else
            {
                this->_RegisterEvent(this->_game.GetElapsedTime() + BONUS_DELAY,
                                     b00st::bind(&EnduranceMap1Entity::_SpawnBonus, *this));
                if (forces > players)
                    delete this->_game.GetForces().front();

                size_t r = static_cast<size_t>(this->_game.R() * this->_bonuses.size());
                if (r >= this->_bonuses.size())
                    r = this->_bonuses.size() - 1;
                (this->*this->_bonuses[r])();
            }
        }

        void EnduranceMap1Entity::_IncreaseLevel(void)
        {
            this->_RegisterEvent(this->_game.GetElapsedTime() + MOB_DELAY,
                                 b00st::bind(&EnduranceMap1Entity::_IncreaseLevel, *this));

            if (this->_monsterGenerators.size() == 0)
            {
                this->_monsterGenerators.push_back(new MonsterGeneratorEntity(this->_game, 3, this->_level * 1.4f, MonsterGeneratorEntity::WEAK));
                if (this->_level > 1)
                {
                    this->_monsterGenerators.push_back(new MonsterGeneratorEntity(this->_game, 5, this->_level * 0.8f, MonsterGeneratorEntity::LITTLE_ROBOT));
                    if (this->_level > 2)
                        this->_monsterGenerators.push_back(new MonsterGeneratorEntity(this->_game, 8, this->_level * 0.3f, MonsterGeneratorEntity::LITTLE_ROBOT_REVERSE));
                }
                if (this->_level % 5 == 0 && this->_level != 0)
                    new MonsterGeneratorEntity(this->_game, 8, 1, MonsterGeneratorEntity::LITTLE_ROBOT_REVERSE);
            }
            else
            {
                for (std::vector<MonsterGeneratorEntity*>::iterator it = this->_monsterGenerators.begin(),
                     ite = this->_monsterGenerators.end() ; it != ite ; ++it)
                {
                    (*it)->delay *= 0.8f;
                    (*it)->number *= 1.2f;
                }
            }
        }

        void EnduranceMap1Entity::_PrepareForBoss(void)
        {
            for (std::vector<MonsterGeneratorEntity*>::iterator it = this->_monsterGenerators.begin(),
                 ite = this->_monsterGenerators.end() ; it != ite ; ++it)
                delete *it;
            this->_monsterGenerators.clear();

            this->_ClearEvents();
            this->_RegisterEvent(this->_game.GetElapsedTime() + BOSS_SECOND_DELAY,
                                 b00st::bind(&EnduranceMap1Entity::_SpawnBoss, *this));

            this->_wallGenerator.StopSpecial();
        }

        void EnduranceMap1Entity::_SpawnBoss(void)
        {
            new Boss1Entity(this->_game, this->_level);
        }

        void EnduranceMap1Entity::_SpawnForceBonus(void)
        {
            new BonusCarrierMobEntity(this->_game, 50 + this->_game.R() * 140, BonusInteraction::FORCE, Resources::BONUS_FORCE);
        }

        void EnduranceMap1Entity::_SpawnSpeedBonus(void)
        {
            new BonusCarrierMobEntity(this->_game, 50 + this->_game.R() * 140, BonusInteraction::SPEED, Resources::BONUS_SPEED);
        }

        void EnduranceMap1Entity::_SpawnForceDnaStyleBonus(void)
        {
            new BonusCarrierMobEntity(this->_game, 50 + this->_game.R() * 140, BonusInteraction::FORCE_DNA_STYLE, Resources::BONUS_FORCE_DNA_STYLE);
        }

        void EnduranceMap1Entity::_SpawnForceBoingLaserBonus(void)
        {
            new BonusCarrierMobEntity(this->_game, 50 + this->_game.R() * 140, BonusInteraction::FORCE_BOING_LASER, Resources::BONUS_FORCE_BOING_LASER);
        }

        void EnduranceMap1Entity::_SpawnForceFlameThrowerBonus(void)
        {
            new BonusCarrierMobEntity(this->_game, 50 + this->_game.R() * 140, BonusInteraction::FORCE_FLAME_THROWER, Resources::BONUS_FORCE_FLAME_THROWER);
        }

        void EnduranceMap1Entity::_SpawnForceExplosiveBonus(void)
        {
            new BonusCarrierMobEntity(this->_game, 50 + this->_game.R() * 140, BonusInteraction::FORCE_EXPLOSIVE, Resources::BONUS_FORCE_EXPLOSIVE);
        }

    }
}
