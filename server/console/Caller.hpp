
#ifndef __CALLER_HPP__
# define __CALLER_HPP__

#include "String.hpp"

namespace Gmgp
{
    namespace Server
    {
        /**
         * StaticCaller is able to call a static function
         */
        template<typename ReturnType>
            struct StaticCaller
            {
                /// function with no argument
                template<typename FunctionType>
                    static std::string call(FunctionType function)
                    {
                        return String(function());
                    }

                /// function with one argument
                template<typename FunctionType, typename Arg1Type>
                    static std::string call(FunctionType function, Arg1Type a1)
                    {
                        return String(function(a1));
                    }

            };

        /**
         * StaticCaller specialisation with no return type
         */
        template<>
            struct StaticCaller<void>
            {
                /// function with no argument
                template<typename FunctionType>
                    static std::string call(FunctionType function)
                    {
                        function();
                        return "";
                    }

                /// function with one argument
                template<typename FunctionType, typename Arg1Type>
                    static std::string call(FunctionType function, Arg1Type a1)
                    {
                        function(a1);
                        return "";
                    }
            };

        /**
         * ObjectCaller can call method of a class instance
         */
        template<typename ReturnType, typename Class>
            struct ObjectCaller
            {
                /// method with no argument
                template<typename FunctionType>
                    static std::string call(Class object, FunctionType method)
                    {
                        return String((object.*method)());
                    }

                /// method with one argument
                template<typename FunctionType, typename Arg1Type>
                    static std::string call(Class object, FunctionType method, Arg1Type a1)
                    {
                        return String((object.*method)(a1));
                    }

                /// method with two argument
                template<typename FunctionType, typename Arg1Type, typename Arg2Type>
                    static std::string call(Class object, FunctionType method, Arg1Type a1, Arg2Type a2)
                    {
                        return String((object.*method)(a1, a2));
                    }

            };

        /**
         * ObjectCaller specialisation with no return type
         */
        template<typename Class>
            struct ObjectCaller<void, Class>
            {
                /// method with no argument
                template<typename FunctionType>
                    static std::string call(Class object, FunctionType method)
                    {
                        (object.*method)();
                        return "";
                    }

                /// method with one argument
                template<typename FunctionType, typename Arg1Type>
                    static std::string call(Class object, FunctionType method, Arg1Type a1)
                    {
                        (object.*method)(a1);
                        return "";
                    }

                /// method with one argument
                template<typename FunctionType, typename Arg1Type, typename Arg2Type>
                    static std::string call(Class object, FunctionType method, Arg1Type a1, Arg2Type a2)
                    {
                        (object.*method)(a1, a2);
                        return "";
                    }
            };



    }
}

#endif

