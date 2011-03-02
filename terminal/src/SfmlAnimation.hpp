#ifndef __SFMLANIMATION_HPP__
#define __SFMLANIMATION_HPP__

#include <SFML/Graphics.hpp>
#include "String.hpp"

namespace Gmgp
{
    namespace Terminal
    {

        class SfmlAnimation :
            private sf::NonCopyable
        {
            public:
                SfmlAnimation(String const& path, size_t frames, size_t delay, bool isVertical, bool smoothing);
                ~SfmlAnimation();
                bool IsLoaded();
                void Load();
                sf::Image& GetImage();
                size_t GetFrames();
                size_t GetDelay();
                bool IsVertical();
            private:
                sf::Image _image;
                String _path;
                size_t _frames;
                size_t _delay;
                bool _isVertical;
                bool _loaded;
                bool _smoothing;
        };

    }
}

#endif

