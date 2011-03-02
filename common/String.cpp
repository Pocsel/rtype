#include "String.hpp"

namespace Gmgp
{

    std::string const String::_whitespaces = " \t\r\n";

    void String::ltrim(std::string const& whitespaces)
    {
        std::size_t pos = this->find_first_not_of(whitespaces);
        this->erase(0, pos);
    }

}

