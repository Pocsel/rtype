#include "LuaResourceInfo.hpp"
#include "Constants.hpp"

namespace Gmgp
{
    namespace Server
    {

        LuaResourceInfo::LuaResourceInfo(String const& path, String const& functionName) :
            _functionName(functionName)
        {
            this->SetPath(path);
        }

        LuaResourceInfo::~LuaResourceInfo()
        {
        }

        void LuaResourceInfo::FillPacket(Packet& packet) const
        {
            packet.Write8(Packet::I_HAVE_THIS);
            packet.Write16(this->GetId());
            packet.Write8(LUA);
            packet.WriteString(this->GetPath());
            packet.WriteString(this->_functionName);
        }

        AResourceInfo* LuaResourceInfo::Clone(void) const
        {
            AResourceInfo* nuInfo = new LuaResourceInfo(this->GetPath(), this->_functionName);
            nuInfo->SetId(this->GetId());
            return nuInfo;
        }

    }
}

