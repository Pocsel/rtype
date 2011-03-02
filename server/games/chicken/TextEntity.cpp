#include "TextEntity.hpp"
#include "Game.hpp"
#include "ItemManager.hpp"
#include "Log.hpp"

namespace Gmgp
{
    namespace Server
    {

        int TextEntity::ID = 0;

        TextEntity::TextEntity(Game& game, uint16_t resourceId, float spacing, uint16_t playerId /* = 0 */) :
            Entity(game, "Text", playerId), _resourceId(resourceId), _spacing(spacing), _autoRemove(false), _autoRemoveTime(0), _removeStyle(NONE)
        {
        }

        TextEntity::~TextEntity()
        {
            this->_RemoveChars(this->_removeStyle);
        }

        void TextEntity::SetRemoveStyle(RemoveStyle style)
        {
            this->_removeStyle = style;
        }

        TextEntity::RemoveStyle TextEntity::GetRemoveStyle() const
        {
            return this->_removeStyle;
        }

        void TextEntity::EnableAutoRemove(float time)
        {
            this->_autoRemove = true;
            this->_autoRemoveTime = time;
        }

        void TextEntity::DisableAutoRemove()
        {
            this->_autoRemove = false;
        }

        bool TextEntity::HasAutoRemove() const
        {
            return this->_autoRemove;
        }

        void TextEntity::Run(float time)
        {
            if (this->_autoRemove && this->_autoRemoveTime <= time)
                delete this;
        }

        void TextEntity::SetBlinking(size_t freq)
        {
            std::list<Item*>::iterator it = this->_chars.begin();
            std::list<Item*>::iterator itEnd = this->_chars.end();
            for (; it != itEnd; ++it)
                if (*it != 0)
                    (*it)->SetBlinking(freq);
        }

        void TextEntity::SetSpeed(float x, float y)
        {
            std::list<Item*>::iterator it = this->_chars.begin();
            std::list<Item*>::iterator itEnd = this->_chars.end();
            for (; it != itEnd; ++it)
                if (*it != 0)
                {
                    (*it)->SetSpeedX(x);
                    (*it)->SetSpeedY(y);
                }
        }

        void TextEntity::SetAccel(float x, float y)
        {
            std::list<Item*>::iterator it = this->_chars.begin();
            std::list<Item*>::iterator itEnd = this->_chars.end();
            for (; it != itEnd; ++it)
                if (*it != 0)
                {
                    (*it)->SetAccelX(x);
                    (*it)->SetAccelY(y);
                }
        }

        void TextEntity::SetPosition(float x, float y, uint8_t z /* = 128 */)
        {
            float curX = x;
            std::list<Item*>::iterator it = this->_chars.begin();
            std::list<Item*>::iterator itEnd = this->_chars.end();
            for (; it != itEnd; ++it)
                if (*it != 0)
                {
                    (*it)->SetPositionX(curX);
                    (*it)->SetPositionY(y);
                    (*it)->SetPositionZ(z);
                    curX += this->_spacing;
                }
                else
                    curX += this->_spacing;
        }

        void TextEntity::SetText(String const& text)
        {
            this->_RemoveChars(NONE);
            this->_text = text;
            this->SetName("Text (\"" + text + "\")");
            std::string str = text;
            std::string::iterator it = str.begin();
            std::string::iterator itEnd = str.end();
            for (; it != itEnd; ++it)
            {
                if (*it >= 33 && *it <= 126)
                {
                    Item* c = new Item(this->_game.GetElapsedTime());
                    this->_game.GetItemManager().AddItem(c);
                    c->SetResourceId(this->_resourceId);
                    c->SetPlayerId(this->GetPlayerId());
                    c->SetFrame(*it - 33);
                    this->_chars.push_back(c);
                }
                else
                    this->_chars.push_back(0);
            }
        }

        void TextEntity::_RemoveChars(RemoveStyle style)
        {
            std::list<Item*>::iterator it = this->_chars.begin();
            std::list<Item*>::iterator itEnd = this->_chars.end();
            for (; it != itEnd; ++it)
            {
                if (*it == 0)
                    continue;
                if (style == NICE)
                {
                    (*it)->SetBlinking(40);
                    (*it)->SetSpeedX(-200 + this->_game.R() * 400);
                    (*it)->SetSpeedY(150 - this->_game.R() * 600);
                    (*it)->SetAccelY(250 + this->_game.R() * 100);
                }
                if (style != NONE)
                {
                    (*it)->SetDisapear(true);
                    // on les supprimme de la liste cote serveur
                    // et on envoie aussi leurs modifs au client
                    this->_game.GetItemManager().RemoveItem(*it, false, true);
                }
                else
                    this->_game.GetItemManager().RemoveItem(*it);
                delete *it;
            }
            this->_chars.clear();
        }

        uint16_t TextEntity::GetResourceId() const
        {
            return this->_resourceId;
        }

        float TextEntity::GetSpacing() const
        {
            return this->_spacing;
        }

        String const& TextEntity::GetText() const
        {
            return this->_text;
        }

    }
}

