#ifndef COMMON2__ENTITY_HPP__
#define COMMON2__ENTITY_HPP__

#include "NonCopyable.hpp"
#include "String.hpp"

namespace Gmgp
{
    namespace Server
    {

        template<typename E, typename G>
            class Common2Entity : private b00st::NonCopyable
        {
        public:
            explicit Common2Entity(G& game, String const& name, uint16_t playerId = 0);
            virtual ~Common2Entity();
            virtual void GenerateInteractions(float time);
            virtual void Run(float time);
            void SetName(String const& name);
            String const& GetName() const;
            uint16_t GetPlayerId() const;
            void SetPlayerId(uint16_t playerId);

        protected:
            G& _game;

        private:
            String _name;
            uint16_t _playerId;
        };

    }
}

#endif

