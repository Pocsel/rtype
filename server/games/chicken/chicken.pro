TEMPLATE = lib
TARGET = chicken
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

INCLUDEPATH += ../common \
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
# Game
#
HEADERS += Game.hpp \
           Player.hpp \
           Entity.hpp \
           ChickenEntity.hpp \
           TextEntity.hpp \
           BackgroundEntity.hpp \
           PlayerEntity.hpp \
           ChickenGeneratorEntity.hpp \
           ScoreBoardEntity.hpp \
           DamageInteraction.hpp \

SOURCES += GetGameInstance.cpp \
           Game.cpp \
           Player.cpp \
           Entity.cpp \
           ChickenEntity.cpp \
           TextEntity.cpp \
           BackgroundEntity.cpp \
           PlayerEntity.cpp \
           ChickenGeneratorEntity.cpp \
           ScoreBoardEntity.cpp \
           DamageInteraction.cpp \

