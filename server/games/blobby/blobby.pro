TEMPLATE = lib
TARGET = blobby
CONFIG += warn_on

QMAKE_CXXFLAGS_DEBUG += -DDEBUG

unix {
    CONFIG += plugin
    DESTDIR = ..
    QMAKE_CFLAGS_SHLIB = -fPIC -Wall -Wextra -include stdint.h -include cstdlib
    QMAKE_CXXFLAGS_SHLIB = -fPIC -Wall -Wextra -include stdint.h -include cstdlib
}

win32 {
    CONFIG += dll
    debug:DESTDIR  = ./debug
    release:DESTDIR  = ./release
    LIBS = -lws2_32
    DEFINES -= UNICODE
    INCLUDEPATH += ../../../windows
    QMAKE_CXXFLAGS = "/FI Types.hpp" "/Fo.\\objs\\$(ConfigurationName)\\" "/Fd.\\objs\\$(ConfigurationName)\\"

    QMAKE_POST_LINK = "copy \"$(TargetPath)\" ..\\"
}

INCLUDEPATH += \
               ../common \
               ../common2 \
               ../../../common \
               ../../../b00st \
               ../../networkabstract \
               ../../threadsabstract \
               ../../logic \
               ../ \

#
# Common
#
HEADERS += \
            ../AResourceInfo.hpp \
            ../IGame.hpp \
            ../IServerProxy.hpp \

SOURCES += \
            ../AResourceInfo.cpp \


HEADERS += \
            ../common/AInteraction.hpp \
            ../common/AnimationResourceInfo.hpp \
            ../common/BasicGame.hpp \
            ../common/BasicPlayer.hpp \
            ../common/Circle.hpp \
            ../common/Clock.hpp \
            ../common/EntityManager.hpp \
            ../common/InteractionManager.hpp \
            ../common/Item.hpp \
            ../common/ItemManager.hpp \
            ../common/PlayerManager.hpp \
            ../common/Point.hpp \
            ../common/QuadTree.hpp \
            ../common/Rect.hpp \
            ../common/ResourceManager.hpp \
            ../common/Shape.hpp \
            ../common/SoundResourceInfo.hpp \

SOURCES += \
            ../common/AnimationResourceInfo.cpp \
            ../common/BasicPlayer.cpp \
            ../common/Circle.cpp \
            ../common/Clock.cpp \
            ../common/Item.cpp \
            ../common/Point.cpp \
            ../common/Rect.cpp \
            ../common/Shape.cpp \
            ../common/SoundResourceInfo.cpp \


HEADERS += \
            ../../threadsabstract/Mutex.hpp \
            ../../threadsabstract/ScopeLock.hpp \
            ../../threadsabstract/Thread.hpp \

SOURCES += \
            ../../threadsabstract/Mutex.cpp \
            ../../threadsabstract/Thread.cpp \


HEADERS += \
            ../../../common/Constants.hpp \
            ../../../common/Log.hpp \
            ../../../common/Packet.hpp \
            ../../../common/String.hpp \

SOURCES += \
            ../../../common/Packet.cpp \
            ../../../common/String.cpp \

#
# Common2
#
HEADERS += \
            Common2Decorator.hpp \
            Common2Entity.cpp \
            Common2Entity.hpp \
            Common2Game.cpp \
            Common2Game.hpp \
            Common2ManagerEntity.cpp \
            Common2ManagerEntity.hpp \
            Common2Player.cpp \
            Common2PlayerEntity.cpp \
            Common2PlayerEntity.hpp \
            Common2Player.hpp \
            Common2Resources.hpp \
            Common2TextEntity.cpp \
            Common2TextEntity.hpp \

#
# Game
#
HEADERS += \
            Entity.hpp \
            Game.hpp \
            ManagerEntity.hpp \
            PlayerEntity.hpp \
            BallEntity.hpp \
            Resources.hpp \


SOURCES += \
            C2Entity.cpp \
            C2Game.cpp \
            C2ManagerEntity.cpp \
            C2Player.cpp \
            C2PlayerEntity.cpp \
            C2TextEntity.cpp \
            Entity.cpp \
            Game.cpp \
            ManagerEntity.cpp \
            PlayerEntity.cpp \
            GetGameInstance.cpp \
            BallEntity.cpp \

