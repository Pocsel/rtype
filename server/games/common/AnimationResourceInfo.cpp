#include "AnimationResourceInfo.hpp"
#include "Constants.hpp"

namespace Gmgp
{
    namespace Server
    {

        AnimationResourceInfo::AnimationResourceInfo(String const& path, size_t frames, size_t delay, bool isVertical) :
            _frames(frames), _delay(delay), _isVertical(isVertical)
        {
            this->SetPath(path);
        }

        AnimationResourceInfo::~AnimationResourceInfo()
        {
        }

        void AnimationResourceInfo::FillPacket(Packet& packet) const
        {
            packet.Write8(Packet::I_HAVE_THIS);
            packet.Write16(this->GetId());
            packet.Write8(ANIMATION);
            packet.WriteString(this->GetPath());
            packet.Write16(this->_frames);
            packet.Write16(this->_delay);
            packet.Write8(this->_isVertical);
        }

        AResourceInfo* AnimationResourceInfo::Clone(void) const
        {
            AResourceInfo* nuInfo = new AnimationResourceInfo(this->GetPath(), this->_frames, this->_delay, this->_isVertical);
            nuInfo->SetId(this->GetId());
            return nuInfo;
        }

    }
}

