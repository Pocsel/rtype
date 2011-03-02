#ifndef __GAMEENTITY_HPP__
#define __GAMEENTITY_HPP__

#include "NonCopyable.hpp"
#include "String.hpp"
#include "Point.hpp"
#include "Circle.hpp"
#include "Rect.hpp"
#include "SmartPtr.hpp"
#include "AInteraction.hpp"

namespace Gmgp
{
    namespace Server
    {

        class Game;

        class GameEntity : private b00st::NonCopyable
        {
        public:
            typedef b00st::SmartPtr<AInteraction<GameEntity> > InteractionPtr;

        public:
            explicit GameEntity(Game& game, String const& name, uint16_t playerId = 0);
            virtual ~GameEntity();
            virtual void GenerateInteractions(float time);
            virtual void Run(float time);
            void SetName(String const& name);
            String const& GetName() const;
            uint16_t GetPlayerId() const;
            void SetPlayerId(uint16_t playerId);

            // Interactions

        protected:
            Game& _game;

        private:
            String _name;
            uint16_t _playerId;
        };

    }
}

#endif

