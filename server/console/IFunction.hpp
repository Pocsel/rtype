
#ifndef __IFUNCTION_HPP__
# define __IFUNCTION_HPP__

#include <string>

namespace Gmgp
{
    namespace Server
    {

        class IFunction
        {
        public:
            virtual ~IFunction() {}
            virtual std::string operator ()(std::string const& params) = 0;
        };

    }
}


#endif

