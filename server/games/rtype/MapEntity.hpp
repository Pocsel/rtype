
#ifndef MAPENTITY_HPP_
# define MAPENTITY_HPP_

#include <list>

#include "GameEntity.hpp"
#include "functor.hpp"
#include "Item.hpp"

namespace Gmgp
{
    namespace Server
    {

        class MapEntity : public GameEntity
        {
        private:
            typedef FUNCTOR1(void) EventHandler;

            struct Event
            {
                Event(float t, EventHandler const& h) : time(t), handler(h)
                {
                }
                float time;
                EventHandler handler;
            };

        protected:
            MapEntity(Game& game);

        public:
            virtual ~MapEntity(void);

            virtual void Run(float time);

        protected:
            void _RegisterEvent(float time, EventHandler const& handler);
            void _ClearEvents(void);

        private:
            static void _Nothing(void);
            std::list<Event> _events;
        };

    }
}

#endif // !MAPENTITY_HPP_
