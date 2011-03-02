
#ifndef SMARTPTR_HPP_
# define SMARTPTR_HPP_

namespace b00st
{

    template<typename T>
        class SmartPtr
        {
        public:
            explicit SmartPtr(void)
                : _count(0)
            {
            }

            explicit SmartPtr(T* ptr)
                : _count(new unsigned int), _ptr(ptr)
            {
                *this->_count = 1;
            }

            explicit SmartPtr(SmartPtr<T> const& smartPtr)
                : _count(smartPtr._count), _ptr(smartPtr._ptr)
            {
                if (this->_count != 0)
                    ++(*this->_count);
            }

            ~SmartPtr(void)
            {
                if (this->_count != 0)
                {
                    --(*this->_count);
                    if (*this->_count == 0)
                    {
                        delete this->_count;
                        delete this->_ptr;
                    }
                }
            }

            SmartPtr<T>& operator =(SmartPtr<T> const& smartPtr)
            {
                if (this->_count != 0)
                {
                    --(*this->_count);
                    if (*this->_count == 0)
                    {
                        delete this->_count;
                        delete this->_ptr;
                    }
                }
                this->_count = smartPtr._count;
                this->_ptr = smartPtr._ptr;
                if (this->_count != 0)
                    ++(*this->_count);
                return *this;
            }

            SmartPtr<T>& operator =(T* ptr)
            {
                if (this->_count != 0)
                {
                    --(*this->_count);
                    if (*this->_count == 0)
                    {
                        delete this->_count;
                        delete this->_ptr;
                    }
                }
                this->_count = new unsigned int;
                *this->_count = 1;
                this->_ptr = ptr;
                return *this;
            }

            T& operator *(void) const
            {
                return *this->_ptr;
            }

            T* operator ->(void) const
            {
                return this->_ptr;
            }

            T* Get(void) const
            {
                return this->_ptr;
            }

        private:
            unsigned int* _count;
            T* _ptr;
        };

}

#endif // !SMARTPTR_HPP_
