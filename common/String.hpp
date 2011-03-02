#ifndef __STRING_HPP__
#define __STRING_HPP__

#include <typeinfo>
#include <stdexcept>
#include <string>
#include <sstream>
#include <iostream>

namespace Gmgp
{

    class String : public std::string
    {
        private:
            static std::string const _whitespaces;

        public:
            template<typename T>
                String(T const& val)
                {
                    std::stringstream ss;
                    ss << val;
                    if (ss.fail())
                        throw std::runtime_error(std::string("Cannot convert from ") +
                                typeid(T).name() + " to String");
                    *this = ss.str();
                }

            String() : std::string() {}
            String(std::string const& str) : std::string(str) {}
            String(char const* str) : std::string(str) {}
            String(String const& s) : std::string(s) {}
            String(char const* str, size_t size) : std::string(str, size) {}

            template<typename T>
                String& operator >>(T& val)
                {
                    std::stringstream ss(*this);
                    ss >> val;
                    if (ss.fail())
                        throw std::runtime_error(std::string("Cannot extract ") + typeid(T).name() +
                                " from String: " + *this);
                    std::string left;
                    std::getline(ss, left);
                    *this = left;
                    return *this;
                }
            template<typename T>
                String operator +(T const& val) const
                {
                    String res = *this;
                    res.append(String(val));
                    return res;
                }

            template<typename T>
                String& operator += (T const& val)
                {
                    this->append(String(val));
                    return *this;
                }

            void ltrim(std::string const& whitespaces = _whitespaces);
    };

}

#endif

