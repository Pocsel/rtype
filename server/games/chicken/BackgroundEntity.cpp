
#include "BackgroundEntity.hpp"
#include "Game.hpp"
#include "ItemManager.hpp"
#include "ResourceManager.hpp"

namespace Gmgp
{
    namespace Server
    {

            BackgroundEntity::BackgroundEntity(Game& game)
                : Entity(game, "Background")
            {
                this->_sprite.SetResourceId(this->_game.GetResourceManager().GetResourceId(Game::BACKGROUND_KFC));
                this->_sprite.SetPositionX(320);
                this->_sprite.SetPositionY(240);
                this->_sprite.SetPositionZ(0);
                this->_game.GetItemManager().AddItem(&this->_sprite);

                this->_music.SetResourceId(this->_game.GetResourceManager().GetResourceId(Game::MUSIC));
                this->_game.GetItemManager().AddItem(&this->_music);
            }

            BackgroundEntity::~BackgroundEntity(void)
            {
                this->_game.GetItemManager().RemoveItem(&this->_sprite);
                this->_game.GetItemManager().RemoveItem(&this->_music);
            }

    }
}
