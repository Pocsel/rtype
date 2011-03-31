
# Packages
#find_package(Threads)

# Sources
file(GLOB mainmenu_base_src
    ../AResourceInfo.hpp
    ../IGame.hpp
    ../IServerProxy.hpp
    ../AResourceInfo.cpp
    ../common/AInteraction.hpp
    ../common/AnimationResourceInfo.hpp
    ../common/BasicGame.hpp
    ../common/BasicPlayer.hpp
    ../common/Circle.hpp
    ../common/Clock.hpp
    ../common/EntityManager.hpp
    ../common/InteractionManager.hpp
    ../common/Item.hpp
    ../common/ItemManager.hpp
    ../common/PlayerManager.hpp
    ../common/Point.hpp
    ../common/QuadTree.hpp
    ../common/Rect.hpp
    ../common/ResourceManager.hpp
    ../common/Shape.hpp
    ../common/SoundResourceInfo.hpp
    ../common/AnimationResourceInfo.cpp
    ../common/BasicPlayer.cpp
    ../common/Circle.cpp
    ../common/Clock.cpp
    ../common/Item.cpp
    ../common/Point.cpp
    ../common/Rect.cpp
    ../common/Shape.cpp
    ../common/SoundResourceInfo.cpp
    ../../threadsabstract/Mutex.hpp
    ../../threadsabstract/ScopeLock.hpp
    ../../threadsabstract/Thread.hpp
    ../../threadsabstract/Mutex.cpp
    ../../threadsabstract/Thread.cpp
    ../../../common/Constants.hpp
    ../../../common/Log.hpp
    ../../../common/Packet.hpp
    ../../../common/String.hpp
    ../../../common/Packet.cpp
    ../../../common/String.cpp
    Game.hpp
    Player.hpp
    Entity.hpp
    MenuEntity.hpp
    ButtonEntity.hpp
    GetGameInstance.cpp
    Game.cpp
    Player.cpp
    Entity.cpp
    MenuEntity.cpp
    ButtonEntity.cpp
    )


if (UNIX)

else(UNIX)
    set(INCLUDE_DIR ../../../windows)
endif(UNIX)

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${INCLUDE_DIR}
    ../common
    ../../logic
    ../../networkabstract
    ../../threadsabstract
    ../../console
    ../../games
    ../../../common
    ../../../b00st
    .)

list(APPEND
    mainmenu_src
    ${mainmenu_base_src}
    )
add_library(mainmenu SHARED
    ${mainmenu_src}
    )

set(LIBRARY_OUTPUT_PATH ..)

target_link_libraries(mainmenu
    ${CMAKE_THREAD_LIBS_INIT}
    ${MOAR_LIB}
    ${NETWORK_LIB}
    )
