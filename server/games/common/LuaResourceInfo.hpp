#ifndef __LUARESOURCEINFO_HPP__
#define __LUARESOURCEINFO_HPP__

#include "AResourceInfo.hpp"

namespace Gmgp
{
    namespace Server
    {

        class LuaResourceInfo :
            public AResourceInfo
        {
            public:
                explicit LuaResourceInfo(String const& path, String const& functionName);
                ~LuaResourceInfo();
                void FillPacket(Packet& packet) const;
                AResourceInfo* Clone(void) const;

            private:
                String _functionName;
        };

    }
}


#endif

