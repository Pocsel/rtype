#include <stdexcept>
#include <cstring>
#include <iomanip>

#ifdef _WIN32 //windows
    #include <Winsock2.h>
#else //unix
    #include <arpa/inet.h>
#endif

#include "Packet.hpp"
#include "Log.hpp"

namespace Gmgp
{

    Packet::Packet() :
        _size(0), _allocSize(INITIALSIZE), _offset(2)
    {
        this->_data = new char[INITIALSIZE];
        this->_WriteSize();
    }

    Packet::Packet(Packet const& packet) :
        _size(packet._size), _allocSize(packet._allocSize), _offset(packet._offset)
    {
        this->_Resize(this->_allocSize);
        ::memcpy(this->_data, packet._data, this->_size + 2);
        this->_WriteSize();
    }

    Packet::~Packet()
    {
        delete [] this->_data;
    }

    Packet& Packet::operator =(Packet const& packet)
    {
        if (this == &packet)
            return *this;
        this->_size = packet._size;
        this->_allocSize = packet._allocSize;
        this->_offset = packet._offset;
        this->_Resize(this->_allocSize);
        ::memcpy(this->_data, packet._data, this->_size + 2);
        this->_WriteSize();
        return (*this);
    }

    size_t Packet::BytesLeft() const
    {
        return this->_size - this->_offset + 2;
    }

    void Packet::Dump() const
    {
        Log::D("Packet dump (" + String(this->_size + 2) + " bytes total) :");
        for (size_t i = 0; i < this->_size + 2; ++i)
        {
            std::cout << std::setfill('0') << std::setw(2) << std::hex << static_cast<uint32_t>(this->_data[i]);
            std::cout << " ";
        }
        std::cout << std::endl;
    }

    void Packet::WriteString(String const& val)
    {
        this->Write16(val.size());
        for (size_t i = 0; i != val.size(); ++i)
            this->_WriteByte(val[i]);
    }

    void Packet::Write8(uint8_t val)
    {
        this->_WriteByte(static_cast<char>(val));
    }

    void Packet::Write16(uint16_t val)
    {
        val = htons(val);
        this->_WriteByte(*(reinterpret_cast<char*>(&val)));
        this->_WriteByte(*(reinterpret_cast<char*>(&val) + 1));
    }

    void Packet::Write32(uint32_t val)
    {
        val = htonl(val);
        this->_WriteByte(*(reinterpret_cast<char*>(&val)));
        this->_WriteByte(*(reinterpret_cast<char*>(&val) + 1));
        this->_WriteByte(*(reinterpret_cast<char*>(&val) + 2));
        this->_WriteByte(*(reinterpret_cast<char*>(&val) + 3));
    }

    void Packet::WriteFloat(float val)
    {
        this->_WriteByte(*(reinterpret_cast<char*>(&val)));
        this->_WriteByte(*(reinterpret_cast<char*>(&val) + 1));
        this->_WriteByte(*(reinterpret_cast<char*>(&val) + 2));
        this->_WriteByte(*(reinterpret_cast<char*>(&val) + 3));
    }

    uint8_t Packet::Read8() const
    {
        if (this->_offset < this->_size + 2)
            return this->_data[this->_offset++];
        throw std::runtime_error("packet too small to read");
    }

    uint16_t Packet::Read16() const
    {
        if (this->_offset + 1 < this->_size + 2)
        {
            uint16_t const* ret = reinterpret_cast<uint16_t const*>(&this->_data[this->_offset]);
            this->_offset += 2;
            return ntohs(*ret);
        }
        throw std::runtime_error("packet too small to read");
    }

    uint32_t Packet::Read32() const
    {
        if (this->_offset + 3 < this->_size + 2)
        {
            uint32_t const* ret = reinterpret_cast<uint32_t const*>(&this->_data[this->_offset]);
            this->_offset += 4;
            return ntohl(*ret);
        }
        throw std::runtime_error("packet too small to read");
    }

    float Packet::ReadFloat() const
    {
        if (this->_offset + 3 < this->_size + 2)
        {
            float const* ret = reinterpret_cast<float const*>(&this->_data[this->_offset]);
            this->_offset += 4;
            return *ret;
        }
        throw std::runtime_error("packet too small to read");
    }

    String Packet::ReadString() const
    {
        size_t size = this->Read16();
        String ret;
        for (size_t i = 0; i < size; ++i)
            ret += this->Read8();
        return ret;
    }

    void Packet::Clear()
    {
        this->_size = 0;
        this->_offset = 2;
        this->_WriteSize();
    }

    void Packet::WriteData(char const* data, size_t size)
    {
        if (this->_allocSize < size + 2)
            this->_Resize(size + 2);
        ::memcpy(this->_data + 2, data, size);
        this->_size = size;
        this->_offset = 2;
        this->_WriteSize();
    }

    void Packet::_Resize(size_t target)
    {
        Log::D("Reallocating packet from " + String(this->_allocSize) + " bytes to " + String(target) + " bytes (size " + String(this->_size) + ").");
        char* tmp = this->_data;
        this->_data = new char[target];
        ::memcpy(this->_data, tmp, this->_allocSize);
        this->_allocSize = target;
        delete [] tmp;
    }

    void Packet::_WriteByte(char byte)
    {
        if (this->_offset >= _allocSize)
            this->_Resize(_allocSize + SIZESTEP);
        this->_data[this->_offset] = byte;
        ++this->_offset;
        if (this->_offset - 2 > this->_size)
            this->_size = this->_offset - 2;
        this->_WriteSize();
    }

    void Packet::_WriteSize()
    {
        uint16_t size = htons(static_cast<uint16_t>(this->_size));
        this->_data[0] = *(reinterpret_cast<char*>(&size));
        this->_data[1] = *(reinterpret_cast<char*>(&size) + 1);
    }

    char const* Packet::GetData() const
    {
        return this->_data + 2;
    }

    char const* Packet::GetCompleteData() const
    {
        return this->_data;
    }

    size_t Packet::GetSize() const
    {
        return this->_size;
    }

    size_t Packet::GetCompleteSize() const
    {
        return this->_size + 2;
    }

}

