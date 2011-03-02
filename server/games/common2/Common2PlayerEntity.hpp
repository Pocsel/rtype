#ifndef COMMON2__PLAYERENTITY_HPP__
#define COMMON2__PLAYERENTITY_HPP__

#include "Item.hpp"
#include "String.hpp"

namespace Gmgp
{
    namespace Server
    {

        template<typename E, typename G, typename PE>
            class Common2PlayerEntity : public E
        {
        public:
            explicit Common2PlayerEntity(G& game, uint16_t playerId, String const& nick);
            virtual ~Common2PlayerEntity();

            int GetScore() const;
            void AddScore(int s);

            String const& GetNick() const;

            int GetColorId() const;
            virtual bool IsAlive() const;
            virtual void LastAlive();


        protected:
            int _score;
        private:
            int _colorId;
            String _nick;
        };

    }
}

#endif

