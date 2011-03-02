
#include "GarbageSpawnerEntity.hpp"
#include "Game.hpp"
#include "WallInteraction.hpp"
#include "TriggerInteraction.hpp"
#include "Resources.hpp"
#include "GarbageEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        GarbageSpawnerEntity::GarbageSpawnerEntity(Game& game, bool up)
            : WallEntity(game, up ? Resources::GARBAGE_SPAWNER_UP : Resources::GARBAGE_SPAWNER_DOWN, up, WIDTH, HEIGHT + 16),
            _up(up),
            _curFrame(0),
            _trigger(new TriggerInteraction()),
            _triggered(false),
            _empty(false)
        {
            this->_sprite.SetFrame(0);

            for (unsigned int i = 0; i < MAX_FRAME; ++i)
                this->_actions.push(&GarbageSpawnerEntity::_IncreaseFrame);
            for (unsigned int i = static_cast<unsigned int>(this->_game.R() * 5 + 3); i > 0; --i)
                this->_actions.push(&GarbageSpawnerEntity::_SpawnGarbage);

            this->_garbage.push_back(GarbageInfo(Resources::GARBAGE1, 16, 16));
            this->_garbage.push_back(GarbageInfo(Resources::GARBAGE2, 32, 32));
            this->_garbage.push_back(GarbageInfo(Resources::GARBAGE3, 29, 30));
            this->_garbage.push_back(GarbageInfo(Resources::GARBAGE4, 29, 31));
            this->_garbage.push_back(GarbageInfo(Resources::GARBAGE5, 32, 31));
        }

        GarbageSpawnerEntity::~GarbageSpawnerEntity(void)
        {
        }

        void GarbageSpawnerEntity::GenerateInteractions(float time)
        {
            // Wall
            this->WallEntity::GenerateInteractions(time);

            // Trigger
            if (this->_triggered == false)
            {
                this->_game.GetEntityManager().GetInteractionManager().AddInteraction(this->_trigger,
                                                                                      Rect(this->_sprite.GetPositionX() - WIDTH * 0.5f, 0,
                                                                                           WIDTH, Game::HEIGHT));
            }
        }

        void GarbageSpawnerEntity::Run(float time)
        {
            if (this->_sprite.GetPositionX() + WIDTH * 0.5 < 0)
            {
                delete this;
                return;
            }
            if (this->_triggered == false)
            {
                if (reinterpret_cast<TriggerInteraction*>(this->_trigger.Get())->IsActive())
                {
                    this->_Act();
                    this->_nextActionTime = time + 0.3f;
                    this->_triggered = true;
                }
            }
            else if (this->_empty == false)
            {
                this->_Act();
                this->_nextActionTime = time + 0.2f + this->_game.R() * 0.3f;
            }
        }

        void GarbageSpawnerEntity::_Act(void)
        {
            if (this->_actions.empty())
            {
                this->_empty = true;
                return;
            }
            (this->*_actions.front())();
            this->_actions.pop();
        }

        void GarbageSpawnerEntity::_IncreaseFrame(void)
        {
            this->_sprite.SetFrame(++this->_curFrame);
        }

        void GarbageSpawnerEntity::_SpawnGarbage(void)
        {
            int r = static_cast<int>(this->_game.R() * 5);
            if (r > 4)
                r = 4;
            GarbageInfo const& info = this->_garbage[r];
            new GarbageEntity(this->_game, info.id, this->_up, info.width, info.height, this->_sprite.GetPositionX());
        }

    }
}
