#ifndef COMMON2__GAME_HPP__
#define COMMON2__GAME_HPP__

#include "BasicGame.hpp"
#include "Common2Player.hpp"

namespace Gmgp
{
    namespace Server
    {

        template<typename E, //entity
            typename G, //game
            typename PE, //player entity
            typename ME, //manager entity
            size_t T, //ticks
            size_t W, //width
            size_t H, //height
            size_t P> //players
                class Common2Game : public BasicGame<E, Common2Player<E, G, PE> >
            {
            public:
                enum Constant
                {
                    FULLWIDTH = W,
                    FULLHEIGHT = H,
                    TICKS_TIME = T
                };

            public:
                explicit Common2Game(String const& name);
                ~Common2Game();

                void RegisterPlayerEntity(PE* player);
                void UnregisterPlayerEntity(PE* player);
                size_t GetNumberOfPlayers() const;
                std::list<PE*> const& GetListOfPlayers() const;

            protected:
                void _InitializeCommon2Resources();
                virtual void _InitializeResources();
                void _Load(int id, AResourceInfo* res);

                virtual ME* _CreateManagerEntity() = 0;

            private:
                virtual void _PreRun();
                virtual void _PostRun();

            protected:
                std::list<PE*> _players;

            private:
                ME* _manager;
            };

    }
}

#endif

