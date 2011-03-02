TEMPLATE = app
TARGET = server
CONFIG += thread warn_on

QMAKE_CXXFLAGS_DEBUG += -DDEBUG

unix {
    LIBS = -ldl
    QMAKE_CXXFLAGS = -Wall -Wextra -include stdint.h -include cstdlib
}

win32 {
    LIBS = -lws2_32
    DEFINES -= UNICODE
    QMAKE_CXXFLAGS = "/FI Types.hpp" "/Fo.\\objs\\$(ConfigurationName)\\" "/Fd.\\objs\\$(ConfigurationName)\\"
    CONFIG += console
    debug:DESTDIR  = ./debug
    release:DESTDIR  = ./release
}


INCLUDEPATH = logic             \
              networkabstract   \
              threadsabstract   \
              console           \
              games             \
              ../common         \
              ../b00st          \

win32:INCLUDEPATH += ../windows


SOURCES += main.cpp                             \


SOURCES += ../common/String.cpp                 \
           ../common/Packet.cpp                 \

HEADERS += ../common/Constants.hpp              \
           ../common/Log.hpp                    \
           ../common/Packet.hpp                 \
           ../common/Singleton.hpp              \
           ../common/String.hpp                 \


SOURCES += logic/Server.cpp                     \
           logic/ServerProxy.cpp                \
           logic/Client.cpp                     \
           logic/DLHandler.cpp                  \
           logic/PacketCreator.cpp              \

HEADERS += logic/Client.hpp                     \
           logic/DLHandler.hpp                  \
           logic/Server.hpp                     \
           logic/ServerProxy.hpp                \
           logic/PacketCreator.hpp              \


SOURCES += games/AResourceInfo.cpp              \

HEADERS += games/AResourceInfo.hpp              \
           games/IServerProxy.hpp               \


SOURCES += console/Console.cpp                  \
           console/Functor.cpp                  \

HEADERS += console/Caller.hpp                   \
           console/Console.hpp                  \
           console/Function.hpp                 \
           console/FunctorConsole.hpp           \
           console/IFunction.hpp                \


SOURCES += networkabstract/HostAddress.cpp              \
           networkabstract/SendBuffer.cpp               \
           networkabstract/Service.cpp                  \
           networkabstract/Timer.cpp                    \
           networkabstract/TcpSocketProxy.cpp           \

HEADERS += networkabstract/HostAddress.hpp              \
           networkabstract/IService.hpp                 \
           networkabstract/ITcpSocket.hpp               \
           networkabstract/SendBuffer.hpp               \
           networkabstract/Service.hpp                  \
           networkabstract/SocketFD.hpp                 \
           networkabstract/TcpSocket.hpp                \
           networkabstract/TcpSocketProxy.hpp           \
           networkabstract/Timer.hpp                    \

unix:SOURCES += networkabstract/UnixTcpSocket.cpp       \

unix:HEADERS += networkabstract/UnixTcpSocket.hpp       \

win32:SOURCES += networkabstract/WindowsTcpSocket.cpp   \

win32:HEADERS += networkabstract/WindowsTcpSocket.hpp   \


SOURCES += threadsabstract/Mutex.cpp            \
           threadsabstract/Thread.cpp           \
           threadsabstract/ThreadCondition.cpp  \
           threadsabstract/ThreadPool.cpp       \

HEADERS += threadsabstract/IMutex.hpp           \
           threadsabstract/IThread.hpp          \
           threadsabstract/Mutex.hpp            \
           threadsabstract/ScopeLock.hpp        \
           threadsabstract/Thread.hpp           \
           threadsabstract/ThreadType.hpp       \
           threadsabstract/ThreadCondition.hpp  \
           threadsabstract/ThreadPool.hpp       \


HEADERS += ../b00st/functioncaller.hpp          \
           ../b00st/functiontype.hpp            \
           ../b00st/functor.hpp                 \
           ../b00st/methodcaller.hpp            \
           ../b00st/methodtype.hpp              \
           ../b00st/NonCopyable.hpp             \
           ../b00st/tuple.hpp                   \
           ../b00st/typelist.hpp                \


