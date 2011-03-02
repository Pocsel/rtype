#ifndef __IGAMEVIEW_HPP__
#define __IGAMEVIEW_HPP__

#include "String.hpp"

namespace Gmgp
{
    namespace Terminal
    {

        class IGameView
        {
            public:
                virtual ~IGameView() {}
                virtual void Start() = 0;
                virtual void Stop() = 0;
                virtual bool IsRunning() const = 0;
                virtual void PushData(char const* data, size_t size) = 0;
                virtual void AddAnimation(size_t id, String const& path, size_t frames, size_t delay, bool isVertical) = 0;
                virtual void AddSound(size_t id, String const& path, bool isMusic) = 0;
                virtual void AddLua(size_t id, String const& path, String const& functionName) = 0;
                virtual void SetResolution(size_t width, size_t height) = 0;
                virtual void EnableSmoothing(bool enable) = 0;
                virtual void EnableMovementSmoothing(bool enable) = 0;
                virtual void SetEffectsVolume(size_t vol) = 0;
                virtual void SetMusicVolume(size_t vol) = 0;
                virtual void ConfirmItem(size_t id) = 0;
                virtual void EnableAutoResize(bool enable) = 0;
                virtual void SetResizeFactor(float val) = 0;
        };

    }
}

#endif

