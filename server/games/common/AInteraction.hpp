#ifndef __AINTERACTION_HPP__
#define __AINTERACTION_HPP__

#include <stdexcept>

#include "NonCopyable.hpp"
#include "Point.hpp"
#include "Rect.hpp"
#include "Circle.hpp"

namespace Gmgp
{
    namespace Server
    {

        template<typename Entity> class AInteraction :
            private b00st::NonCopyable
        {
        public:
            AInteraction(Entity* entity) :
                _creator(entity)
            {
            }

            virtual ~AInteraction()
            {
            }

            virtual bool Interact(Entity& entity) = 0;

            virtual void ChangeCreator(Entity* entity)
            {
                this->_creator = entity;
            }

            virtual Entity* GetCreator() const
            {
                return this->_creator;
            }

        private:
            Entity* _creator;
        };

    }
}

#endif

