#include "SpriteItem.hpp"
#include "Log.hpp"

namespace Gmgp
{
    namespace Terminal
    {

        SpriteItem::SpriteItem(size_t id, size_t resourceId, SfmlGameView& view, SfmlRenderer& renderer) :
            _view(view), _renderer(renderer), _anim(0), _posZ(128), _posX(-10000), _posY(-10000), _speedX(0), _speedY(0), _accelX(0), _accelY(0), _lifeTimeMs(0), _lifeTimeCycles(0), _disapear(false), _blinking(0), _cursor(false), _currentFrame(0), _lastFrameTime(0), _lastBlinkTime(0), _blinkDisplay(false), _lifeTimeSet(false), _spawned(false), _posSetX(false), _posSetY(false), _luaFile(0), _luaSetTime(0), _id(id)
        {
            this->SetResourceId(resourceId);
            this->_sprite.SetPosition(-10000, -10000);
            this->SetPositionZ(128);
        }

        SpriteItem::~SpriteItem()
        {
            Log::D("SpriteItem destructor.");
            this->_LuaDelete();
        }

        void SpriteItem::_LuaDelete()
        {
            if (this->_luaFile != 0)
                this->_luaFile->Delete(this);
        }

        size_t SpriteItem::GetId() const
        {
            return this->_id;
        }

        void SpriteItem::Render(sf::RenderWindow* app, float time)
        {
            // resource check
            if (this->_anim == 0)
            {
                Log::D("Sprite auto deletion: invalid resource.");
                this->_renderer.DeleteItem(this);
                return;
            }
            // life time check
            if (this->_lifeTimeMs > 0 && !this->_lifeTimeSet)
            {
                this->_lifeTime = time;
                this->_lifeTimeSet = true;
            }
            if (this->_lifeTimeSet && (time - this->_lifeTime) * 1000.0f > this->_lifeTimeMs)
            {
                Log::D("Sprite auto deletion: life finished (" + String(this->_lifeTimeMs) + " ms).");
                this->_renderer.DeleteItem(this);
                return;
            }
            // movement
            if (this->_luaFile != 0)
                this->_luaFile->Run(this, this->_luaSetTime, time, app->GetFrameTime());
            float timeOffset = app->GetFrameTime();
            this->_speedX += this->_accelX * timeOffset;
            this->_speedY += this->_accelY * timeOffset;
            this->_posX += this->_speedX * timeOffset;
            this->_posY += this->_speedY * timeOffset;
            if (this->_view.MovementSmoothing())
            {
                this->_sprite.SetX(this->_sprite.GetPosition().x + (this->_posX - this->_sprite.GetPosition().x) / 2);
                this->_sprite.SetY(this->_sprite.GetPosition().y + (this->_posY - this->_sprite.GetPosition().y) / 2);
            }
            else
            {
                this->_sprite.SetX(this->_posX);
                this->_sprite.SetY(this->_posY);
            }
            // cursor
            if (this->_cursor)
            {
                this->_sprite.SetX(this->_renderer.GetMouseX());
                this->_sprite.SetY(this->_renderer.GetMouseY());
            }
            // disapear check
            if (this->_disapear && !this->_cursor)
            {
                if (this->_sprite.GetPosition().x + this->_GetWidth() / 2 < 0 ||
                        this->_sprite.GetPosition().x - this->_GetWidth() / 2 > this->_renderer.GetWidth() ||
                        this->_sprite.GetPosition().y + this->_GetHeight() / 2 < 0 ||
                        this->_sprite.GetPosition().y - this->_GetHeight() / 2 > this->_renderer.GetHeight())
                {
                    Log::D("Sprite auto deletion: disappearance.");
                    this->_renderer.DeleteItem(this);
                    return;
                }
            }
            // animation
            if (this->_anim != 0 && this->_anim->GetDelay() != 0)
            {
                if (!this->_spawned)
                {
                    this->_lastFrameTime = time;
                    this->_spawned = true;
                }
                size_t newFrames = 0;
                for (; this->_lastFrameTime + this->_anim->GetDelay() * 0.001f < time ; this->_lastFrameTime += this->_anim->GetDelay() * 0.001f) //NEW
                    ++newFrames;
                if (newFrames > 0)
                    this->_SetAnimationFrame(this->_currentFrame + newFrames);
            }
            // life cycle check
            if (this->_lifeTimeCycles > 0 && this->_cyclesCounter >= this->_lifeTimeCycles)
            {
                Log::D("Sprite auto deletion: life finished (" + String(this->_lifeTimeCycles) + " cycles).");
                this->_renderer.DeleteItem(this);
                return;
            }
            // rendering
            if (this->_blinking > 0)
            {
                if ((time - this->_lastBlinkTime) * 1000.0f > this->_blinking)
                {
                    this->_blinkDisplay = !this->_blinkDisplay;
                    this->_lastBlinkTime = time;
                }
                if (this->_blinkDisplay)
                    app->Draw(this->_sprite);
            }
            else
                app->Draw(this->_sprite);
        }

        void SpriteItem::_SetAnimationFrame(size_t frame)
        {
            if (this->_anim == 0)
                return;
            if (frame >= this->_anim->GetFrames())
                ++this->_cyclesCounter;
            frame %= this->_anim->GetFrames();
            size_t width = this->_GetWidth();
            size_t height = this->_GetHeight();
            sf::IntRect rect;
            if (this->_anim->IsVertical())
            {
                rect.Top = frame * height;
                rect.Left = 0;
            }
            else
            {
                rect.Top = 0;
                rect.Left = frame * width;
            }
            rect.Right = rect.Left + width;
            rect.Bottom = rect.Top + height;
            this->_sprite.SetSubRect(rect);
            this->_currentFrame = frame;
        }

        size_t SpriteItem::_GetWidth()
        {
            if (this->_anim == 0)
                return 0;
            if (this->_anim->IsVertical())
                return this->_anim->GetImage().GetWidth();
            return this->_anim->GetImage().GetWidth() / this->_anim->GetFrames();
        }

        size_t SpriteItem::_GetHeight()
        {
            if (this->_anim == 0)
                return 0;
            if (this->_anim->IsVertical())
                return this->_anim->GetImage().GetHeight() / this->_anim->GetFrames();
            return this->_anim->GetImage().GetHeight();
        }

        void SpriteItem::SetResourceId(size_t id)
        {
            this->_anim = _view.GetAnimation(id);
            if (this->_anim == 0)
            {
                Log::W("Could not find animation " + String(id) + ".");
                return;
            }
            this->_sprite.SetImage(this->_anim->GetImage());
            this->_sprite.SetCenter(this->_GetWidth() / 2, this->_GetHeight() / 2);
            this->_SetAnimationFrame(0);
        }

        void SpriteItem::SetLuaId(size_t id)
        {
            this->_LuaDelete();
            this->_luaFile = this->_view.GetScript(id);
            this->_luaSetTime = this->_view.GetTime();
            if (this->_luaFile != 0)
                this->_luaFile->Create(this);
        }

        void SpriteItem::SetPositionX(float pos)
        {
            this->_posX = pos;
            if (!this->_view.MovementSmoothing() || !this->_posSetX)
            {
                this->_sprite.SetX(pos);
                this->_posSetX = true;
            }
        }

        float SpriteItem::GetPositionX() const
        {
            return this->_posX;
        }

        void SpriteItem::SetPositionY(float pos)
        {
            this->_posY = pos;
            if (!this->_view.MovementSmoothing() || !this->_posSetY)
            {
                this->_sprite.SetY(pos);
                this->_posSetY = true;
            }
        }

        float SpriteItem::GetPositionY() const
        {
            return this->_posY;
        }

        void SpriteItem::SetSpeedX(float speed)
        {
            this->_speedX = speed;
        }

        float SpriteItem::GetSpeedX() const
        {
            return this->_speedX;
        }

        void SpriteItem::SetSpeedY(float speed)
        {
            this->_speedY = speed;
        }

        float SpriteItem::GetSpeedY() const
        {
            return this->_speedY;
        }

        void SpriteItem::SetAccelX(float accel)
        {
            this->_accelX = accel;
        }

        float SpriteItem::GetAccelX() const
        {
            return this->_accelX;
        }

        void SpriteItem::SetAccelY(float accel)
        {
            this->_accelY = accel;
        }

        float SpriteItem::GetAccelY() const
        {
            return this->_accelY;
        }

        void SpriteItem::SetLifeTimeMs(size_t ms)
        {
            this->_lifeTimeSet = false;
            this->_lifeTimeMs = ms;
        }

        void SpriteItem::SetLifeTimeCycles(size_t cycles)
        {
            this->_lifeTimeCycles = cycles;
            this->_cyclesCounter = 0;
        }

        void SpriteItem::SetDisapear(bool enable)
        {
            this->_disapear = enable;
        }

        void SpriteItem::SetPositionZ(size_t pos)
        {
            this->_renderer.RemoveItem(this, this->_posZ);
            this->_posZ = pos;
            this->_renderer.AddItem(this, this->_posZ);
        }

        void SpriteItem::SetBlinking(size_t freq)
        {
            this->_blinking = freq;
        }

        void SpriteItem::SetCursor(bool enable)
        {
            this->_cursor = enable;
        }

        void SpriteItem::SetFrame(size_t frame)
        {
            this->_SetAnimationFrame(frame);
        }

        size_t SpriteItem::GetFrame() const
        {
            return this->_currentFrame;
        }

    }
}

