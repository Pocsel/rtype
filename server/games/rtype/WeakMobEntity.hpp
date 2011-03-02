
#ifndef WEAKMOBENTITY_HPP_
# define WEAKMOBENTITY_HPP_

#include "MonsterEntity.hpp"
#include "Item.hpp"

namespace Gmgp
{
    namespace Server
    {

        class WeakMobEntity : public MonsterEntity
        {
        public:
            explicit WeakMobEntity(Game& game, float y);
            ~WeakMobEntity();

        protected:
            void _Run(float time);

        private:
            float _nextDirectionTime;
        };

    }
}

#endif // !WEAKMOBENTITY_HPP_
