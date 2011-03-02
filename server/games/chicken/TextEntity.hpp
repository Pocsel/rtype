#ifndef __TEXTENTITY_HPP__
#define __TEXTENTITY_HPP__

#include <list>

#include "Entity.hpp"
#include "Item.hpp"

namespace Gmgp
{
    namespace Server
    {

        class TextEntity : public Entity
        {
            public:
                enum RemoveStyle
                {
                    NONE,
                    NICE
                };
                explicit TextEntity(Game& game, uint16_t resourceId, float spacing, uint16_t playerId = 0);
                virtual ~TextEntity();
                void Run(float time);
                void SetText(String const& text);
                String const& GetText() const;
                uint16_t GetResourceId() const;
                float GetSpacing() const;
                void EnableAutoRemove(float time);
                bool HasAutoRemove() const;
                void DisableAutoRemove();
                void SetPosition(float x, float y, uint8_t z = 128);
                void SetBlinking(size_t freq);
                void SetSpeed(float x, float y);
                void SetAccel(float x, float y);
                void SetRemoveStyle(RemoveStyle style);
                RemoveStyle GetRemoveStyle() const;

            private:
                void _RemoveChars(RemoveStyle style);
                String _text;
                uint16_t _resourceId;
                float _spacing;
                std::list<Item*> _chars;
                bool _autoRemove;
                float _autoRemoveTime;
                RemoveStyle _removeStyle;
                int _id;
                static int ID;
        };

    }
}

#endif

