#include "ChickenEntity.hpp"
#include "Game.hpp"
#include "ChickenGeneratorEntity.hpp"
#include "PlayerManager.hpp"
#include "Constants.hpp"
#include "Log.hpp"

namespace Gmgp
{
    namespace Server
    {

        ChickenGeneratorEntity::ChickenGeneratorEntity(Game& game, uint16_t id) :
            Entity(game, "Chicken generator", id), _nextSpawn(0)
        {
        }

        ChickenGeneratorEntity::~ChickenGeneratorEntity(void)
        {
        }

        void ChickenGeneratorEntity::Run(float time)
        {
            try
            {
                Player& p = this->_game.GetPlayerManager().GetPlayer(this->GetPlayerId());
                if (p.KeyPressed(Key::K))
                {
                    if (p.KeyPressed(Key::S))
                        new ChickenEntity(this->_game, true);
                    else
                        new ChickenEntity(this->_game);
                }
            }
            catch (std::exception&)
            {
            }
            if (time > this->_nextSpawn)
            {
                new ChickenEntity(this->_game);
                this->_nextSpawn = time + 0.1f + this->_game.R() * 1.1f;
            }
        }

    }
}

