#include "SfmlAnimation.hpp"
#include "Log.hpp"

namespace Gmgp
{
    namespace Terminal
    {

        SfmlAnimation::SfmlAnimation(String const& path, size_t frames, size_t delay, bool isVertical, bool smoothing) :
            _path(path), _frames(frames), _delay(delay), _isVertical(isVertical), _loaded(false), _smoothing(smoothing)
        {
            Log::D("New animation: " + _path + ".");
            if (this->_frames == 0)
            {
                this->_frames = 1;
                Log::W("Received an animation with 0 frames, setting to 1.");
            }
        }

        SfmlAnimation::~SfmlAnimation()
        {
            Log::D("Destroying animation: " + _path + ".");
        }

        bool SfmlAnimation::IsLoaded()
        {
            return this->_loaded;
        }

        void SfmlAnimation::Load()
        {
            if (this->_loaded)
                return;
            if (this->_image.LoadFromFile(this->_path))
                Log::D("Image " + this->_path + " loaded.");
            else
                Log::W("Could not load image " + this->_path + ".");
            this->_image.SetSmooth(this->_smoothing);
            this->_loaded = true;
        }

        sf::Image& SfmlAnimation::GetImage()
        {
            this->Load();
            return this->_image;
        }

        size_t SfmlAnimation::GetFrames()
        {
            return this->_frames;
        }

        size_t SfmlAnimation::GetDelay()
        {
            return this->_delay;
        }

        bool SfmlAnimation::IsVertical()
        {
            return this->_isVertical;
        }

    }
}

