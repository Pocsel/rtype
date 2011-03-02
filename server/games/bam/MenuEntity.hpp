#ifndef __MENUENTITY_HPP__
#define __MENUENTITY_HPP__

#include "NonCopyable.hpp"
#include "String.hpp"

namespace Gmgp
{
    namespace Server
    {

        class MainGame;

        class MenuEntity : private b00st::NonCopyable
        {
            public:
                explicit MenuEntity(MainGame& game, String const& name, uint16_t playerId = 0);
                virtual ~MenuEntity();
                virtual void GenerateInteractions(float time);
                virtual void Run(float time);
                void SetName(String const& name);
                String const& GetName() const;
                uint16_t GetPlayerId() const;
                void SetPlayerId(uint16_t playerId);

            protected:
                MainGame& _game;

            private:
                String _name;
                uint16_t _playerId;
        };

    }
}

#endif

