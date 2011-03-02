
#ifndef __CONSOLE_HPP__
# define __CONSOLE_HPP__

# include <string>
# include <map>

# include "FunctorConsole.hpp"
# include "Function.hpp"

namespace Gmgp
{
    namespace Server
    {

        class Console
        {
        private:
            std::map<std::string, Functor> _commands;
            std::map<std::string, std::string> _help;

        public:
            Console();

            /// static function with no parameter
            template<typename ReturnType>
                void bind(std::string const& name,
                          ReturnType (*function)(),
                          std::string const& help = "");

            /// static function with one parameter
            template<typename ReturnType, typename Arg1Type>
                void bind(std::string const& name,
                          ReturnType (*function)(Arg1Type),
                          std::string const& help = "");

            /// object method with 0 parameter
            template <typename Class, typename ObjectType, typename ReturnType>
                void bind(std::string const& name,
                          ObjectType& object,
                          ReturnType (Class::*method)(),
                          std::string const& help = "");

            /// const object method with 0 parameter
            template <typename Class, typename ObjectType, typename ReturnType>
                void bind(std::string const& name,
                          ObjectType const& object,
                          ReturnType (Class::*method)() const,
                          std::string const& help = "");

            /// object method with 1 parameter
            template <typename Class, typename ObjectType, typename ReturnType, typename Arg1Type>
                void bind(std::string const& name,
                          ObjectType& object,
                          ReturnType (Class::*method)(Arg1Type),
                          std::string const& help = "");

            /// const object method with 1 parameter
            template <typename Class, typename ObjectType, typename ReturnType, typename Arg1Type>
                void bind(std::string const& name,
                          ObjectType const& object,
                          ReturnType (Class::*method)(Arg1Type) const,
                          std::string const& help = "");

            /// object method with 2 parameter
            template <typename Class, typename ObjectType, typename ReturnType, typename Arg1Type, typename Arg2Type>
                void bind(std::string const& name,
                          ObjectType& object,
                          ReturnType (Class::*method)(Arg1Type, Arg2Type),
                          std::string const& help = "");

            /// const object method with 2 parameter
            template <typename Class, typename ObjectType, typename ReturnType, typename Arg1Type, typename Arg2Type>
                void bind(std::string const& name,
                          ObjectType const& object,
                          ReturnType (Class::*method)(Arg1Type, Arg2Type) const,
                          std::string const& help = "");

            /// return list of commands in a string
            std::string help() const;

            /// process a command
            std::string sendLine(std::string const& line);
        };

        /////////////////////////////////////////////////////////////////////////////
        /// static function with no parameter
        template<typename ReturnType>
            void Console::bind(std::string const& name,
                               ReturnType (*function)(),
                               std::string const& help)
            {
                typedef StaticFunction0<ReturnType> type_t;
                this->_commands[name] = new type_t(function);
                this->_help[name] = help;
            }

        /////////////////////////////////////////////////////////////////////////////
        /// static function with one parameter
        template<typename ReturnType, typename Arg1Type>
            void Console::bind(std::string const& name,
                               ReturnType (*function)(Arg1Type),
                               std::string const& help)
            {
                typedef StaticFunction1<ReturnType, Arg1Type> type_t;
                this->_commands[name] = new type_t(function);
                this->_help[name] = help;
            }

        /////////////////////////////////////////////////////////////////////////////
        /// object method with 0 parameter
        template <typename Class, typename ObjectType, typename ReturnType>
            void Console::bind(std::string const& name,
                               ObjectType& object,
                               ReturnType (Class::*method)(),
                               std::string const& help)
            {
                typedef ObjectMethod0<ObjectType&, ReturnType (Class::*)(), ReturnType> type_t;
                this->_commands[name] = new type_t(object, method);
                this->_help[name] = help;
            }

        /////////////////////////////////////////////////////////////////////////////
        /// const object method with 0 parameter
        template <typename Class, typename ObjectType, typename ReturnType>
            void Console::bind(std::string const& name,
                               ObjectType const& object,
                               ReturnType (Class::*method)() const,
                               std::string const& help)
            {
                typedef ObjectMethod0<ObjectType const&, ReturnType (Class::*)() const, ReturnType> type_t;
                this->_commands[name] = new type_t(object, method);
                this->_help[name] = help;
            }

        /////////////////////////////////////////////////////////////////////////////
        /// object method with 1 parameter
        template <typename Class, typename ObjectType, typename ReturnType, typename Arg1Type>
            void Console::bind(std::string const& name,
                               ObjectType& object,
                               ReturnType (Class::*method)(Arg1Type),
                               std::string const& help)
            {
                typedef ObjectMethod1<ObjectType&, ReturnType (Class::*)(Arg1Type), ReturnType, Arg1Type> type_t;
                this->_commands[name] = new type_t(object, method);
                this->_help[name] = help;
            }

        /////////////////////////////////////////////////////////////////////////////
        /// const object method with 1 parameter
        template <typename Class, typename ObjectType, typename ReturnType, typename Arg1Type>
            void Console::bind(std::string const& name,
                               ObjectType const& object,
                               ReturnType (Class::*method)(Arg1Type) const,
                               std::string const& help)
            {
                typedef ObjectMethod1<ObjectType const&, ReturnType (Class::*)(Arg1Type) const, ReturnType, Arg1Type> type_t;
                this->_commands[name] = new type_t(object, method);
                this->_help[name] = help;
            }

        /////////////////////////////////////////////////////////////////////////////
        /// object method with 2 parameter
        template <typename Class, typename ObjectType, typename ReturnType, typename Arg1Type, typename Arg2Type>
            void Console::bind(std::string const& name,
                               ObjectType& object,
                               ReturnType (Class::*method)(Arg1Type, Arg2Type),
                               std::string const& help)
            {
                typedef ObjectMethod2<ObjectType&, ReturnType (Class::*)(Arg1Type, Arg2Type), ReturnType, Arg1Type, Arg2Type> type_t;
                this->_commands[name] = new type_t(object, method);
                this->_help[name] = help;
            }

        /////////////////////////////////////////////////////////////////////////////
        /// const object method with 2 parameter
        template <typename Class, typename ObjectType, typename ReturnType, typename Arg1Type, typename Arg2Type>
            void Console::bind(std::string const& name,
                               ObjectType const& object,
                               ReturnType (Class::*method)(Arg1Type, Arg2Type) const,
                               std::string const& help)
            {
                typedef ObjectMethod2<ObjectType const&, ReturnType (Class::*)(Arg1Type) const, ReturnType, Arg1Type, Arg2Type> type_t;
                this->_commands[name] = new type_t(object, method);
                this->_help[name] = help;
            }

    }
}

#endif /* !__CONSOLE_HPP__ */
