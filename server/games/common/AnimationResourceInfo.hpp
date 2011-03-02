#ifndef __ANIMATIONRESOURCEINFO_HPP__
#define __ANIMATIONRESOURCEINFO_HPP__

#include "AResourceInfo.hpp"

namespace Gmgp
{
    namespace Server
    {

        class AnimationResourceInfo :
            public AResourceInfo
        {
            public:
                explicit AnimationResourceInfo(String const& path, size_t frames, size_t delay, bool isVertical);
                ~AnimationResourceInfo();
                void FillPacket(Packet& packet) const;
                AResourceInfo* Clone(void) const;
            private:
                size_t _frames;
                size_t _delay;
                bool _isVertical;
        };

    }
}

#endif

