
# Packages
find_package(Threads)
if(UNIX)
    set(MOAR_LIB dl)
endif(UNIX)

# Sources
file(GLOB server_base_src
    "main.cpp"
    "../common/String.cpp"
    "../common/Packet.cpp"
    "../common/Constants.hpp"
    "../common/Log.hpp"
    "../common/Packet.hpp"
    "../common/Singleton.hpp"
    "../common/String.hpp"
    "logic/Server.cpp"
    "logic/ServerProxy.cpp"
    "logic/Client.cpp"
    "logic/DLHandler.cpp"
    "logic/PacketCreator.cpp"
    "logic/Client.hpp"
    "logic/DLHandler.hpp"
    "logic/Server.hpp"
    "logic/ServerProxy.hpp"
    "logic/PacketCreator.hpp"
    "games/AResourceInfo.cpp"
    "games/AResourceInfo.hpp"
    "games/IServerProxy.hpp"
    "console/Console.cpp"
    "console/Functor.cpp"
    "console/Caller.hpp"
    "console/Console.hpp"
    "console/Function.hpp"
    "console/FunctorConsole.hpp"
    "console/IFunction.hpp"
    "networkabstract/HostAddress.cpp"
    "networkabstract/SendBuffer.cpp"
    "networkabstract/Service.cpp"
    "networkabstract/Timer.cpp"
    "networkabstract/TcpSocketProxy.cpp"
    "networkabstract/HostAddress.hpp"
    "networkabstract/IService.hpp"
    "networkabstract/ITcpSocket.hpp"
    "networkabstract/SendBuffer.hpp"
    "networkabstract/Service.hpp"
    "networkabstract/SocketFD.hpp"
    "networkabstract/TcpSocket.hpp"
    "networkabstract/TcpSocketProxy.hpp"
    "networkabstract/Timer.hpp"
    "threadsabstract/Mutex.cpp"
    "threadsabstract/Thread.cpp"
    "threadsabstract/ThreadCondition.cpp"
    "threadsabstract/ThreadPool.cpp"
    "threadsabstract/IMutex.hpp"
    "threadsabstract/IThread.hpp"
    "threadsabstract/Mutex.hpp"
    "threadsabstract/ScopeLock.hpp"
    "threadsabstract/Thread.hpp"
    "threadsabstract/ThreadType.hpp"
    "threadsabstract/ThreadCondition.hpp"
    "threadsabstract/ThreadPool.hpp"
    "../b00st/functioncaller.hpp"
    "../b00st/functiontype.hpp"
    "../b00st/functor.hpp"
    "../b00st/methodcaller.hpp"
    "../b00st/methodtype.hpp"
    "../b00st/NonCopyable.hpp"
    "../b00st/tuple.hpp"
    "../b00st/typelist.hpp"
    )


if (UNIX)
    file(GLOB server_specific_src
        "networkabstract/UnixTcpSocket.cpp"
        "networkabstract/UnixTcpSocket.hpp"
        )
else(UNIX)
    file(GLOB server_specific_src
        "networkabstract/WindowsTcpSocket.cpp"
        "networkabstract/WindowsTcpSocket.hpp"
        )
    set(INCLUDE_DIR ../windows)
endif(UNIX)

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${INCLUDE_DIR}
    logic
    networkabstract
    threadsabstract
    console
    games
    ../common
    ../b00st
    .)

list(APPEND
    server_src
        ${server_base_src}
        ${server_specific_src}
)

add_executable(server
    ${server_src}
)

target_link_libraries(server
    ${CMAKE_THREAD_LIBS_INIT}
    ${MOAR_LIB}
    ${NETWORK_LIB}
    )
