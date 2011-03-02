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

        class EnemyDamageInteraction;
        class FriendlyDamageInteraction;
        class MonsterInteraction;
        class ShipInteraction;
        class WallInteraction;
        class ForceFireInteraction;
        class ForceControlInteraction;
        class ForceAttachInteraction;
        class BonusInteraction;
        class ShieldInteraction;
        class TriggerInteraction;
        class RepulseInteraction;
        class ForceUpgradeInteraction;
        class ForceDowngradeInteraction;
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
            virtual bool Interact(EnemyDamageInteraction& interaction);
            virtual bool Interact(FriendlyDamageInteraction& interaction);
            virtual bool Interact(MonsterInteraction& interaction);
            virtual bool Interact(ShipInteraction& interaction);
            virtual bool Interact(WallInteraction& interaction);
            virtual bool Interact(ForceFireInteraction& interaction);
            virtual bool Interact(ForceControlInteraction& interaction);
            virtual bool Interact(ForceAttachInteraction& interaction);
            virtual bool Interact(BonusInteraction& interaction);
            virtual bool Interact(ShieldInteraction& interaction);
            virtual bool Interact(TriggerInteraction& interaction);
            virtual bool Interact(RepulseInteraction& interaction);
            virtual bool Interact(ForceUpgradeInteraction& interaction);
            virtual bool Interact(ForceDowngradeInteraction& interaction);

        protected:
            Game& _game;

        private:
            String _name;
            uint16_t _playerId;
        };

    }
}

#endif

