
#include <stdexcept>

#include "FunctorConsole.hpp"

namespace Gmgp
{
    namespace Server
    {

        Functor::Functor(IFunction* function) : _function(function)
        {
        }

        std::string Functor::operator ()(std::string const& params) const
        {
            if (this->_function == 0)
                throw std::runtime_error("Functor initialized with a NULL function");
            return (*this->_function)(params);
        }

    }
}
