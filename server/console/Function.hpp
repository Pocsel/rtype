#ifndef __FUNCTION_HPP__
#define __FUNCTION_HPP__

#include <string>

#include "IFunction.hpp"
#include "Caller.hpp"
#include "String.hpp"

namespace Gmgp
{
    namespace Server
    {

        /**
         * Trick to get correct type with template powa
         */
        template <typename T> struct TypeCleaner {typedef T type_t;};
        template <typename T> struct TypeCleaner<T&> {typedef T type_t;};
        template <typename T> struct TypeCleaner<const T> {typedef T type_t;};
        template <typename T> struct TypeCleaner<const T&> {typedef T type_t;};

        /**
         * Static function with no parameter
         */
        template <typename ReturnType>
            class StaticFunction0 : public IFunction
        {
        private:
            typedef ReturnType (*t_function)();
            t_function _function;
            virtual std::string operator ()(std::string const&)
            {
                return StaticCaller<ReturnType>::call(this->_function);
            }

        public:
            StaticFunction0(t_function function) : _function(function) {}
        };

        /**
         * Static function with one parameters
         */
        template <typename ReturnType, typename Arg1Type>
            class StaticFunction1 : public IFunction
        {
        private:
            typedef ReturnType (*t_function)(Arg1Type);
            t_function _function;
            virtual std::string operator ()(std::string const& params)
            {
                typename TypeCleaner<Arg1Type>::type_t a1;
                String(params) >> a1;
                return StaticCaller<ReturnType>::call(this->_function, a1);
            }

        public:
            StaticFunction1(t_function function) : _function(function) {}
        };

        /**
         * Object method with no parameter
         */
        template <typename Class, typename MethodType, typename ReturnType>
            class ObjectMethod0 : public IFunction
        {
        private:
            Class _object;
            MethodType _method;
            virtual std::string operator ()(std::string const&)
            {
                return ObjectCaller<ReturnType, Class>::call(this->_object, this->_method);
            }

        public:
            ObjectMethod0(Class object, MethodType method) : _object(object), _method(method) {}
        };

        /**
         * Object method with one parameter
         */
        template <typename Class, typename MethodType, typename ReturnType, typename Arg1Type>
            class ObjectMethod1 : public IFunction
        {
        private:
            Class _object;
            MethodType _method;
            virtual std::string operator ()(std::string const& params)
            {
                typename TypeCleaner<Arg1Type>::type_t arg1;
                String(params) >> arg1;
                return ObjectCaller<ReturnType, Class>::call(this->_object, this->_method, arg1);
            }

        public:
            ObjectMethod1(Class object, MethodType method) : _object(object), _method(method) {}
        };

        /**
         * Object method with two parameter
         */
        template <typename Class, typename MethodType, typename ReturnType, typename Arg1Type, typename Arg2Type>
            class ObjectMethod2 : public IFunction
        {
        private:
            Class _object;
            MethodType _method;
            virtual std::string operator ()(std::string const& params)
            {
                typename TypeCleaner<Arg1Type>::type_t arg1;
                typename TypeCleaner<Arg2Type>::type_t arg2;
                String(params) >> arg1 >> arg2;
                return ObjectCaller<ReturnType, Class>::call(this->_object, this->_method, arg1, arg2);
            }

        public:
            ObjectMethod2(Class object, MethodType method) : _object(object), _method(method) {}
        };

    }
}

#endif
