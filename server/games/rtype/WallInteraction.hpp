
#ifndef WALLINTERACTION_HPP_
# define WALLINTERACTION_HPP_

#include "AInteraction.hpp"
#include "GameEntity.hpp"
#include "Point.hpp"

namespace Gmgp
{
    namespace Server
    {

        class WallInteraction : public AInteraction<GameEntity>
        {
        public:
            explicit WallInteraction(void);

            ~WallInteraction(void);

            virtual bool Interact(GameEntity& entity);

            void SetPosition(float x, float y);
            Point const& GetPosition(void) const;

            void SetSize(float w, float h);
            Point const& GetSize(void) const;

        private:
            Point _pos;
            Point _size;
        };
    }
}

#endif // !WALLINTERACTION_HPP_
