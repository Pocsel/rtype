#ifndef __NONCOPYABLE_HPP__
#define __NONCOPYABLE_HPP__

namespace b00st
{

    class NonCopyable
    {
        protected:
            NonCopyable() {}
            ~NonCopyable() {}
        private:
            NonCopyable(NonCopyable const&);
            NonCopyable& operator =(NonCopyable const&);
    };

}

#endif

