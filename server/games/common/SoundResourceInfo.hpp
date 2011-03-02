#ifndef __SOUNDRESOURCEINFO_HPP__
#define __SOUNDRESOURCEINFO_HPP__

#include "AResourceInfo.hpp"

namespace Gmgp
{
    namespace Server
    {

        class SoundResourceInfo :
            public AResourceInfo
        {
            public:
                explicit SoundResourceInfo(String const& path, bool isMusic);
                ~SoundResourceInfo();
                void FillPacket(Packet& packet) const;
                AResourceInfo* Clone(void) const;

            private:
                bool _isMusic;
        };

    }
}

#endif

