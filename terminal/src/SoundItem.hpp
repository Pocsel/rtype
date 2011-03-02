#ifndef __SOUNDITEM_HPP__
#define __SOUNDITEM_HPP__

#include "IItem.hpp"
#include "SfmlGameView.hpp"

namespace Gmgp
{
    namespace Terminal
    {

        class SoundItem :
            public IItem, private sf::NonCopyable
        {
            public:
                explicit SoundItem(size_t resourceId, SfmlGameView& view, SfmlRenderer& renderer);
                ~SoundItem();
                void Render(sf::RenderWindow* app, float time);
                void SetResourceId(size_t id);
                void SetPositionX(float pos);
                void SetPositionY(float pos);
                void SetSpeedX(float speed);
                void SetSpeedY(float speed);
                void SetAccelX(float accel);
                void SetAccelY(float accel);
                void SetLifeTimeMs(size_t ms);
                void SetLifeTimeCycles(size_t cycles);
                void SetDisapear(bool enable);
                void SetPositionZ(size_t pos);
                void SetBlinking(size_t freq);
                void SetCursor(bool enable);
                void SetFrame(size_t frame);
                void SetLuaId(size_t id);
            private:
                SfmlGameView& _view;
                SfmlRenderer& _renderer;
                SfmlSound* _resource;
                sf::Sound _sound;
                sf::Music _music;
                size_t _lifeTimeMs;
                size_t _lifeTimeCycles;
                bool _lifeTimeSet;
                float _lifeTime;
                size_t _cyclesCounter;
        };

    }
}

#endif

