#include "SoundResourceInfo.hpp"
#include "Constants.hpp"

namespace Gmgp
{
    namespace Server
    {

        SoundResourceInfo::SoundResourceInfo(String const& path, bool isMusic) :
            _isMusic(isMusic)
        {
            this->SetPath(path);
        }

        SoundResourceInfo::~SoundResourceInfo()
        {
        }

        void SoundResourceInfo::FillPacket(Packet& packet) const
        {
            packet.Write8(Packet::I_HAVE_THIS);
            packet.Write16(this->GetId());
            packet.Write8(SOUND);
            packet.WriteString(this->GetPath());
            packet.Write8(this->_isMusic);
        }

        AResourceInfo* SoundResourceInfo::Clone(void) const
        {
            AResourceInfo* nuInfo = new SoundResourceInfo(this->GetPath(), this->_isMusic);
            nuInfo->SetId(this->GetId());
            return nuInfo;
        }

    }
}

