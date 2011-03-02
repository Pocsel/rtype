#ifndef __PACKET_HPP__
#define __PACKET_HPP__

#include "String.hpp"

namespace Gmgp
{

    /// Generic serialization class for packets (TCP)
    class Packet
    {
        public:
            enum
            {
                IN_GAME = 0,
                ANYONE_THERE = 4,
                PLEASE_COME_IN = 8,
                I_HAVE_THIS = 15,
                I_NEED_THIS = 16,
                TAKE_IT = 23,
                TAKE_SOME_MORE = 42,
                LETS_GO = 69,
                WATCH_THIS_OUT = 88,
                PING = 111,
                PONG = 222
            };

        public:
            Packet();

            Packet(Packet const& packet);

            ~Packet();

            Packet& operator =(Packet const& packet);

            size_t BytesLeft() const;

            void Clear();

            /// Resets all data
            void WriteData(char const* data, size_t size);

            void Write8(uint8_t val);

            void Write16(uint16_t val);

            void Write32(uint32_t val);

            void WriteFloat(float val);

            /// Writes string length bytes + 2 (for string size)
            void WriteString(String const& val);

            /// Reads 1 byte or throws if nothing to read
            uint8_t Read8() const;

            /// Reads 2 bytes or throws if nothing to read
            uint16_t Read16() const;

            /// Reads 4 bytes or throws if nothing to read
            uint32_t Read32() const;

            /// Reads 4 bytes or throws if nothing to read
            float ReadFloat() const;

            /// Reads a string or throws if nothing to read
            String ReadString() const;

            /// Returns the size of the data
            size_t GetSize() const;

            /// Returns the size of the data + 2 (for data size)
            size_t GetCompleteSize() const;

            /// Returns a pointer to the beginning of the data
            char const* GetData() const;

            /// Returns a pointer to the beginning of the data - 2 (for size)
            char const* GetCompleteData() const;

            void Dump() const;

        private:
            enum
            {
                INITIALSIZE = 1024,
                SIZESTEP = 512
            };
            void _WriteSize();
            void _WriteByte(char byte);
            void _Resize(size_t target);
            char* _data;
            size_t _size;
            size_t _allocSize;
            mutable size_t _offset;
    };

}

#endif

