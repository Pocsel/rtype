#include "MapEntity.hpp"
#include "Resources.hpp"
#include "Game.hpp"

namespace Gmgp
{
    namespace Server
    {

        MapEntity::MapEntity(Game& game) : GameEntity(game, "Map")
        {
        }

        MapEntity::~MapEntity(void)
        {
        }

        void MapEntity::Run(float time)
        {
            for (; this->_events.empty() == false && this->_events.front().time < time ;)
            {
                this->_events.front().handler();
                this->_events.pop_front();
            }
        }

        void MapEntity::_RegisterEvent(float time, EventHandler const& handler)
        {
            for (std::list<Event>::iterator it = this->_events.begin(),
                 ite = this->_events.end() ; it != ite ; ++it)
            {
                if (time < (*it).time)
                {
                    this->_events.insert(it, Event(time, handler));
                    return;
                }
            }
            this->_events.push_back(Event(time, handler));
        }

        void MapEntity::_ClearEvents(void)
        {
            this->_events.clear();
            this->_events.push_back(Event(0, b00st::bind(&MapEntity::_Nothing)));
        }

        void MapEntity::_Nothing(void)
        {
        }

    }
}
