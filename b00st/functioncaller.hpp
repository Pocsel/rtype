/**
 * @file functioncaller.hpp
 * @author <@> @NAME@
 *
 * @section DESCRIPTION
 * @FIXME@
 */

#ifndef __FUNCTIONCALLER_HPP__
# define __FUNCTIONCALLER_HPP__

#include "tuple.hpp"
#include "typelist.hpp"
#include "functiontype.hpp"

namespace b00st
{

    template<typename ReturnType, typename List> struct FunctionCaller;

    template<typename ReturnType>
    struct FunctionCaller<ReturnType, TYPELIST0()>
    {
        typedef TYPELIST0() list_t;
        typedef typename FunctionType<ReturnType, list_t>::type function_t;

        static ReturnType call(function_t function, Tuple<list_t>& args)
        {
            (void)args;
            return function();
        }
    };

    template<typename ReturnType, typename T1>
    struct FunctionCaller<ReturnType, TYPELIST1(T1)>
    {
        typedef TYPELIST1(T1) list_t;
        typedef typename FunctionType<ReturnType, list_t>::type function_t;

        static ReturnType call(function_t function, Tuple<list_t>& args)
        {
            return function(args.val1);
        }
    };

    template<typename ReturnType, typename T1, typename T2>
    struct FunctionCaller<ReturnType, TYPELIST2(T1, T2)>
    {
        typedef TYPELIST2(T1, T2) list_t;
        typedef typename FunctionType<ReturnType, list_t>::type function_t;

        static ReturnType call(function_t function, Tuple<list_t>& args)
        {
            return function(args.val1, args.val2);
        }
    };

}

#endif /* !__FUNCTIONCALLER_HPP__ */

