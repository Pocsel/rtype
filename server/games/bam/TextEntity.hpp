#ifndef __TEXTENTITY_HPP__
#define __TEXTENTITY_HPP__

#include <list>

#include "Item.hpp"
#include "String.hpp"

namespace Gmgp
{
    namespace Server
    {

        template<typename E, typename G>
            class TextEntity : public E
        {
        public:
            enum RemoveStyle
            {
                NONE,
                NICE,
                UP_DOWN,
                LEFT_RIGHT
            };

            explicit TextEntity(G& game, uint16_t resourceId, float spacing, uint16_t playerId = 0) :
                E(game, "Text", playerId), _resourceId(resourceId), _spacing(spacing), _autoRemove(false), _autoRemoveTime(0), _removeStyle(NONE)
            {
            }

            virtual ~TextEntity()
            {
                this->_RemoveChars(this->_removeStyle);
            }

            void Run(float time)
            {
                if (this->_autoRemove && this->_autoRemoveTime <= time)
                    delete this;
            }

            void SetText(String const& text)
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

            String const& GetText() const
            {
                return this->_text;
            }

            uint16_t GetResourceId() const
            {
                return this->_resourceId;
            }

            float GetSpacing() const
            {
                return this->_spacing;
            }

            void EnableAutoRemove(float time)
            {
                this->_autoRemove = true;
                this->_autoRemoveTime = time;
            }

            bool HasAutoRemove() const
            {
                return this->_autoRemove;
            }

            void DisableAutoRemove()
            {
                this->_autoRemove = false;
            }

            void SetPosition(float x, float y, uint8_t z = 128)
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

            void SetBlinking(size_t freq)
            {
                std::list<Item*>::iterator it = this->_chars.begin();
                std::list<Item*>::iterator itEnd = this->_chars.end();
                for (; it != itEnd; ++it)
                    if (*it != 0)
                        (*it)->SetBlinking(freq);
            }

            void SetSpeed(float x, float y)
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

            void SetAccel(float x, float y)
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

            void SetRemoveStyle(RemoveStyle style)
            {
                this->_removeStyle = style;
            }

            RemoveStyle GetRemoveStyle() const
            {
                return this->_removeStyle;
            }

        private:
            void _RemoveChars(RemoveStyle style)
            {
                size_t i = 0;
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
                    else if (style == UP_DOWN)
                    {
                        if (i % 2 == 0)
                            (*it)->SetSpeedY(250);
                        else
                            (*it)->SetSpeedY(-250);
                    }
                    else if (style == LEFT_RIGHT)
                    {
                        if (i % 2 == 0)
                            (*it)->SetSpeedX(250);
                        else
                            (*it)->SetSpeedX(-250);
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
                    ++i;
                }
                this->_chars.clear();
            }

            String _text;
            uint16_t _resourceId;
            float _spacing;
            std::list<Item*> _chars;
            bool _autoRemove;
            float _autoRemoveTime;
            RemoveStyle _removeStyle;
        };

    }
}

#endif

