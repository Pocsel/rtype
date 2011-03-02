#ifndef __SPRITEITEM_HPP__
#define __SPRITEITEM_HPP__

#include "IItem.hpp"
#include "SfmlGameView.hpp"

namespace Gmgp
{
    namespace Terminal
    {

        class SpriteItem :
            public IItem, private sf::NonCopyable
        {
            public:
                explicit SpriteItem(size_t id, size_t resourceId, SfmlGameView& view, SfmlRenderer& renderer);
                ~SpriteItem();
                size_t GetId() const;
                void Render(sf::RenderWindow* app, float time);
                void SetResourceId(size_t id);
                void SetPositionX(float pos);
                float GetPositionX() const;
                void SetPositionY(float pos);
                float GetPositionY() const;
                void SetSpeedX(float speed);
                float GetSpeedX() const;
                void SetSpeedY(float speed);
                float GetSpeedY() const;
                void SetAccelX(float accel);
                float GetAccelX() const;
                void SetAccelY(float accel);
                float GetAccelY() const;
                void SetLifeTimeMs(size_t ms);
                void SetLifeTimeCycles(size_t cycles);
                void SetDisapear(bool enable);
                void SetPositionZ(size_t pos);
                void SetBlinking(size_t freq);
                void SetCursor(bool enable);
                void SetFrame(size_t frame);
                size_t GetFrame() const;
                void SetLuaId(size_t id);
            private:
                void _SetAnimationFrame(size_t frame);
                size_t _GetWidth();
                size_t _GetHeight();
                void _LuaDelete();
                SfmlGameView& _view;
                SfmlRenderer& _renderer;
                SfmlAnimation* _anim;
                sf::Sprite _sprite;
                size_t _posZ;
                float _posX;
                float _posY;
                float _speedX;
                float _speedY;
                float _accelX;
                float _accelY;
                size_t _lifeTimeMs;
                size_t _lifeTimeCycles;
                bool _disapear;
                size_t _blinking;
                bool _cursor;
                size_t _currentFrame;
                float _lastFrameTime;
                float _lastBlinkTime;
                bool _blinkDisplay;
                bool _lifeTimeSet;
                float _lifeTime;
                size_t _cyclesCounter;
                bool _spawned;
                bool _posSetX;
                bool _posSetY;
                LuaFile* _luaFile;
                float _luaSetTime;
                size_t _id;
        };

    }
}

#endif

