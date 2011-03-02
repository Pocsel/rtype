#include "SfmlSound.hpp"
#include "Log.hpp"

namespace Gmgp
{
    namespace Terminal
    {

        SfmlSound::SfmlSound(String const& path, bool isMusic) :
            _path(path), _isMusic(isMusic), _loaded(false)
        {
            Log::D("New sound: " + _path + ".");
        }

        SfmlSound::~SfmlSound()
        {
            Log::D("Destroying sound: " + _path + ".");
        }

        bool SfmlSound::IsMusic()
        {
            return this->_isMusic;
        }

        bool SfmlSound::IsLoaded()
        {
            return this->_loaded;
        }

        String const& SfmlSound::GetPath()
        {
            return this->_path;
        }

        sf::SoundBuffer& SfmlSound::GetSoundBuffer()
        {
            this->Load();
            return this->_buffer;
        }

        void SfmlSound::Load()
        {
            if (this->_loaded)
                return;
            this->_loaded = true;
            if (this->_isMusic)
                Log::W("Trying to load a sound buffer for a music.");
            else
            {
                if (this->_buffer.LoadFromFile(this->_path))
                    Log::D("Sound " + this->_path + " loaded.");
                else
                    Log::W("Could not load sound " + this->_path + ".");
            }
        }

    }
}

