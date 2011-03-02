
#ifndef SENDBUFFER_HPP_
# define SENDBUFFER_HPP_

namespace Gmgp
{
    namespace Server
    {

        class SendBuffer
        {
        public:
            SendBuffer(char const* data, size_t len, bool del = true);
            SendBuffer(SendBuffer const& first);
            ~SendBuffer(void);

            char const* GetData(void) const;
            size_t GetLenght(void) const;

            /// Returns true when buffer is empty
            bool Remove(size_t len);
            bool IsEmpty(void) const;

        private:
            char* _data;
            size_t _len;
            size_t _pos;
            bool _del;
        };

    }
}

#endif // !SENDBUFFER_HPP_
