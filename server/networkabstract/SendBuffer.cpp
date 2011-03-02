
#include <cstring>
#include <stdexcept>

#include "SendBuffer.hpp"

namespace Gmgp
{
    namespace Server
    {

        SendBuffer::SendBuffer(char const* data, size_t len, bool del)
            : _len(len), _pos(0), _del(del)
        {
            this->_data = new char[len];
            ::memcpy(this->_data, data, len);
        }

        SendBuffer::SendBuffer(SendBuffer const& first)
            : _data(first._data), _len(first._len), _pos(first._pos), _del(true)
        {
        }

        SendBuffer::~SendBuffer(void)
        {
            if (this->_del)
                delete[] this->_data;
        }

        char const* SendBuffer::GetData(void) const
        {
            if (this->_len == this->_pos)
                throw std::runtime_error("SendBuffer: cannot get empty data");
            return this->_data + this->_pos;
        }

        size_t SendBuffer::GetLenght(void) const
        {
            return this->_len - this->_pos;
        }

        bool SendBuffer::Remove(size_t len)
        {
            this->_pos += len;
            if (this->_pos > this->_len)
                this->_pos = this->_len;
            return this->_len == this->_pos;
        }

        bool SendBuffer::IsEmpty(void) const
        {
            return this->_len == this->_pos;
        }

    }
}
