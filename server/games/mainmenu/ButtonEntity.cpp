#include "Game.hpp"
#include "ButtonEntity.hpp"
#include "PlayerManager.hpp"

namespace Gmgp
{
    namespace Server
    {

        ButtonEntity::ButtonEntity(Game& game, uint16_t playerId) :
            Entity(game, "Button", playerId), _x(0), _y(0), _z(128), _width(0), _hover(false), _clicked(false)
        {
            this->_text = new TextEntity<Entity, Game>(game, this->_game.GetResourceManager().GetResourceId(Game::FONT), 7, playerId);
            this->_icon.SetResourceId(this->_game.GetResourceManager().GetResourceId(Game::PLUGIN_DISABLED));
            this->_icon.SetPlayerId(playerId);
            this->_game.GetItemManager().AddItem(&this->_icon);
        }

        ButtonEntity::~ButtonEntity()
        {
            this->_game.GetItemManager().RemoveItem(&this->_icon);
            delete this->_text;
        }

        void ButtonEntity::Run(float)
        {
            bool state = this->_Hover();
            if (state && !this->_hover)
            {
                //this->_text->SetBlinking(40);
                this->_icon.SetResourceId(this->_game.GetResourceManager().GetResourceId(Game::PLUGIN));
            }
            else if (!state && this->_hover)
            {
                //this->_text->SetBlinking(0);
                this->_icon.SetResourceId(this->_game.GetResourceManager().GetResourceId(Game::PLUGIN_DISABLED));
            }
            this->_hover = state;
        }

        bool ButtonEntity::Clicked() const
        {
            return this->_clicked;
        }

        bool ButtonEntity::_Hover()
        {
            try
            {
                Player& p = this->_game.GetPlayerManager().GetPlayer(this->GetPlayerId());
                if (p.GetMouseX() >= this->_x - this->_text->GetSpacing() / 2 &&
                    p.GetMouseX() <= this->_x - this->_text->GetSpacing() / 2 + this->_width &&
                    p.GetMouseY() >= this->_y - 5 &&
                    p.GetMouseY() <= this->_y + 5)
                {
                    if (p.ButtonPressed(Mouse::Left))
                        this->_clicked = true;
                    else
                        this->_clicked = false;
                    return true;
                }
            }
            catch (std::exception&)
            {
            }
            this->_clicked = false;
            return false;
        }

        void ButtonEntity::SetText(String const& text)
        {
            this->_text->SetText(text);
            this->_text->SetPosition(this->_x, this->_y, this->_z);
            this->_width = static_cast<size_t>(this->_text->GetSpacing() * text.size());
        }

        void ButtonEntity::SetPosition(float x, float y, uint8_t z /* = 128 */)
        {
            this->_text->SetPosition(x, y, z);
            this->_x = x;
            this->_y = y;
            this->_z = z;
            this->_icon.SetPositionX(x - 15);
            this->_icon.SetPositionY(y);
        }

    }
}

