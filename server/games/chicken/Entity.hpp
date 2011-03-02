#ifndef __ENTITY_HPP__
#define __ENTITY_HPP__

#include "NonCopyable.hpp"
#include "String.hpp"
#include "SmartPtr.hpp"
#include "AInteraction.hpp"

namespace Gmgp
{
    namespace Server
    {

        class DamageInteraction;
        class Game;

        class Entity : private b00st::NonCopyable
        {
        protected:
            typedef b00st::SmartPtr<AInteraction<Entity> > InteractionPtr;

        public:
            explicit Entity(Game& game, String const& name, uint16_t playerId = 0);
            virtual ~Entity();
            virtual void GenerateInteractions(float time);
            virtual void Run(float time);
            void SetName(String const& name);
            String const& GetName() const;
            uint16_t GetPlayerId() const;
            void SetPlayerId(uint16_t playerId);

            // Interactions
            virtual bool Interact(DamageInteraction& interaction);

        protected:
            Game& _game;

        private:
            String _name;
            uint16_t _playerId;
        };

    }
}

#endif

