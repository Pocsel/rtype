

#ifndef __FUNCTOR_HPP__
# define __FUNCTOR_HPP__

#include <string>

#include "IFunction.hpp"

namespace Gmgp
{
    namespace Server
    {

        class Functor
        {
        private:
            IFunction* _function;

        public:
            Functor(IFunction* function = 0);
            std::string operator ()(std::string const& params = "") const;
        };

    }
}

#endif
