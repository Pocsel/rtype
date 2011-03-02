#ifndef __IITEM_HPP__
#define __IITEM_HPP__

#include <SFML/Graphics.hpp>

namespace Gmgp
{
    namespace Terminal
    {

        class IItem
        {
            public:
                virtual ~IItem() {}
                virtual void Render(sf::RenderWindow* app, float time) = 0;
                virtual void SetResourceId(size_t id) = 0;
                virtual void SetPositionX(float pos) = 0;
                virtual void SetPositionY(float pos) = 0;
                virtual void SetSpeedX(float speed) = 0;
                virtual void SetSpeedY(float speed) = 0;
                virtual void SetAccelX(float accel) = 0;
                virtual void SetAccelY(float accel) = 0;
                virtual void SetLifeTimeMs(size_t ms) = 0;
                virtual void SetLifeTimeCycles(size_t cycles) = 0;
                virtual void SetDisapear(bool enable) = 0;
                virtual void SetPositionZ(size_t pos) = 0;
                virtual void SetBlinking(size_t freq) = 0;
                virtual void SetCursor(bool enable) = 0;
                virtual void SetFrame(size_t frame) = 0;
                virtual void SetLuaId(size_t id) = 0;
        };

    }
}

#endif

