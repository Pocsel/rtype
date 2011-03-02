#include "MainGame.hpp"
#include "ButtonEntity.hpp"
#include "PlayerManager.hpp"
#include "Resources.hpp"
#include "MenuPlayer.hpp"

namespace Gmgp
{
    namespace Server
    {

        ButtonEntity::ButtonEntity(MainGame& game, uint16_t playerId) :
            MenuEntity(game, "Button", playerId), _x(0), _y(0), _z(128), _width(0), _hover(false), _clicked(false)
        {
            this->_text = new TextEntity<MenuEntity, MainGame>(game, this->_game.GetResourceManager().GetResourceId(Resources::FONT), 7, playerId);
        }

        ButtonEntity::~ButtonEntity()
        {
            this->_text->SetRemoveStyle(TextEntity<MenuEntity, MainGame>::NICE);
            delete this->_text;
        }

        void ButtonEntity::Run(float)
        {
            bool state = this->_Hover();
            if (state && !this->_hover)
                this->_text->SetBlinking(40);
            else if (!state && this->_hover)
                this->_text->SetBlinking(0);
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
                MenuPlayer& p = this->_game.GetPlayerManager().GetPlayer(this->GetPlayerId());
                if (p.GetMouseX() >= this->_x - this->_text->GetSpacing() / 2 &&
                    p.GetMouseX() <= this->_x - this->_text->GetSpacing() / 2 + this->_width &&
                    p.GetMouseY() >= this->_y - 5 &&
                    p.GetMouseY() <= this->_y + 5)
                {
                    if (p.ButtonClicked(Mouse::Left))
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
            if (this->_hover)
                this->_text->SetBlinking(40);
            this->_width = static_cast<size_t>(this->_text->GetSpacing() * text.size());
        }

        void ButtonEntity::SetPosition(float x, float y, uint8_t z /* = 128 */)
        {
            this->_text->SetPosition(x, y, z);
            this->_x = x;
            this->_y = y;
            this->_z = z;
        }

    }
}

