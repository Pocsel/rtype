
#ifndef ARESOURCEINFO_HPP_
# define ARESOURCEINFO_HPP_

#include "String.hpp"
#include "Packet.hpp"

namespace Gmgp
{
    namespace Server
    {

        class AResourceInfo
        {
        public:
            AResourceInfo(void);
            virtual ~AResourceInfo(void);

            String const& GetPath(void) const;
            void SetPath(String const& path);
            uint16_t GetId(void) const;
            void SetId(uint16_t id);
            virtual void FillPacket(Packet& packet) const = 0;
            virtual AResourceInfo* Clone(void) const = 0;

        private:
            String _path;
            uint16_t _id;
        };

    }
}

#endif // !ARESOURCEINFO_HPP_
