#include "Game.hpp"

extern "C"
{

    DLL_EXPORT Gmgp::Server::IGame* GetGameInstance(void)
    {
        return new Gmgp::Server::Game();
    }

}

