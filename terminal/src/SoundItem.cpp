#include "SoundItem.hpp"
#include "Log.hpp"

namespace Gmgp
{
    namespace Terminal
    {

        SoundItem::SoundItem(size_t resourceId, SfmlGameView& view, SfmlRenderer& renderer) :
            _view(view), _renderer(renderer), _resource(0), _lifeTimeMs(0), _lifeTimeCycles(0), _lifeTimeSet(false), _lifeTime(0), _cyclesCounter(0)
        {
            this->SetResourceId(resourceId);
            this->_renderer.AddItem(this, 256); // sounds are "rendered" last
            this->_sound.SetLoop(false);
            this->_sound.SetVolume(this->_view.GetEffectsVolume());
            this->_music.SetLoop(false);
            this->_music.SetVolume(this->_view.GetMusicVolume());
        }

        SoundItem::~SoundItem()
        {
            Log::D("SoundItem destructor.");
            this->_music.Stop();
            this->_sound.Stop();
        }

        void SoundItem::Render(sf::RenderWindow*, float time)
        {
            // resource check
            if (this->_resource == 0)
            {
                Log::D("Sound auto deletion: invalid resource.");
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
                Log::D("Sound auto deletion: life finished (" + String(this->_lifeTimeMs) + " ms).");
                this->_renderer.DeleteItem(this);
                return;
            }
            if (this->_resource != 0)
            {
                // looping
                bool replay = (this->_resource->IsMusic() && this->_music.GetStatus() != sf::Sound::Playing) ||
                              (!this->_resource->IsMusic() && this->_sound.GetStatus() != sf::Sound::Playing);
                // life cycle check
                if (!replay)
                    return;
                ++this->_cyclesCounter;
                if (this->_lifeTimeCycles > 0 && this->_cyclesCounter >= this->_lifeTimeCycles)
                {
                    Log::D("Sound auto deletion: life finished (" + String(this->_lifeTimeCycles) + " cycles).");
                    this->_renderer.DeleteItem(this);
                    return;
                }
                Log::D("Sound loop.");
                if (this->_resource->IsMusic())
                    this->_music.Play();
                else
                    this->_sound.Play();
            }
        }

        void SoundItem::SetResourceId(size_t id)
        {
            this->_resource = _view.GetSound(id);
            if (this->_resource == 0)
            {
                Log::W("Could not find sound " + String(id) + ".");
                return;
            }
            this->_sound.Stop();
            this->_music.Stop();
            if (this->_resource->IsMusic())
            {
                if (this->_music.OpenFromFile(this->_resource->GetPath()))
                {
                    this->_music.Play();
                    Log::D("Music " + this->_resource->GetPath() + " loaded.");
                }
                else
                {
                    Log::W("Could not load music " + this->_resource->GetPath() + ".");
                    this->_resource = 0; // will destroy the sound with a correct error msg
                }
            }
            else
            {
                this->_sound.SetBuffer(this->_resource->GetSoundBuffer());
                this->_sound.Play();
            }
        }

        void SoundItem::SetPositionX(float)
        {
        }

        void SoundItem::SetPositionY(float)
        {
        }

        void SoundItem::SetSpeedX(float)
        {
        }

        void SoundItem::SetSpeedY(float)
        {
        }

        void SoundItem::SetAccelX(float)
        {
        }

        void SoundItem::SetAccelY(float)
        {
        }

        void SoundItem::SetLifeTimeMs(size_t ms)
        {
            this->_lifeTimeSet = false;
            this->_lifeTimeMs = ms;
        }

        void SoundItem::SetLifeTimeCycles(size_t cycles)
        {
            this->_lifeTimeCycles = cycles;
            this->_cyclesCounter = 0;
        }

        void SoundItem::SetDisapear(bool)
        {
        }

        void SoundItem::SetPositionZ(size_t)
        {
        }

        void SoundItem::SetBlinking(size_t)
        {
        }

        void SoundItem::SetCursor(bool)
        {
        }

        void SoundItem::SetFrame(size_t)
        {
        }

        void SoundItem::SetLuaId(size_t)
        {
        }

    }
}

