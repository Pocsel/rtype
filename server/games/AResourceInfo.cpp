
#include "AResourceInfo.hpp"

namespace Gmgp
{
    namespace Server
    {

        AResourceInfo::AResourceInfo(void) : _id(0)
        {
        }

        AResourceInfo::~AResourceInfo(void)
        {
        }

        String const& AResourceInfo::GetPath(void) const
        {
            return this->_path;
        }

        void AResourceInfo::SetPath(String const& path)
        {
            this->_path = path;
        }

        uint16_t AResourceInfo::GetId(void) const
        {
            return this->_id;
        }

        void AResourceInfo::SetId(uint16_t id)
        {
            this->_id = id;
        }

    }
}


