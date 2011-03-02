#ifndef __SFMLSOUND_HPP__
#define __SFMLSOUND_HPP__

#include <SFML/Audio.hpp>
#include "String.hpp"

namespace Gmgp
{
    namespace Terminal
    {

        class SfmlSound :
            private sf::NonCopyable
        {
            public:
                SfmlSound(String const& path, bool isMusic);
                ~SfmlSound();
                bool IsLoaded();
                void Load();
                bool IsMusic();
                sf::SoundBuffer& GetSoundBuffer();
                String const& GetPath();
            private:
                String _path;
                bool _isMusic;
                bool _loaded;
                sf::SoundBuffer _buffer;
        };

    }
}

#endif

