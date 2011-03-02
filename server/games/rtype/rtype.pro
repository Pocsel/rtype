TEMPLATE = lib
TARGET = rtype
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
            ../common/LuaResourceInfo.hpp \
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
            ../common/LuaResourceInfo.cpp \
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
HEADERS += MenuEntity.hpp \
           GameEntity.hpp \
           Game.hpp \
           GamePlayer.hpp \
           MainGame.hpp \
           MenuPlayer.hpp \
           Utils.hpp \

SOURCES += MenuEntity.cpp \
           GameEntity.cpp \
           Game.cpp \
           GamePlayer.cpp \
           GetGameInstance.cpp \
           MainGame.cpp \
           MenuPlayer.cpp \
           Utils.cpp \


HEADERS += TextEntity.hpp \
           ButtonEntity.hpp \
           MainMenuEntity.hpp \
           BackgroundEntity.hpp \
           PlayerEntity.hpp \
           ForceEntity.hpp \
           RoomEntity.hpp \
           Map1Entity.hpp \
           FileMapEntity.hpp \
           MissileEntity.hpp \
           MissileLauncherMobEntity.hpp \
           ParticleGeneratorEntity.hpp \
           TimerEntity.hpp \
           LuaMissileEntity.hpp \

SOURCES += ButtonEntity.cpp \
           MainMenuEntity.cpp \
           BackgroundEntity.cpp \
           PlayerEntity.cpp \
           ForceEntity.cpp \
           RoomEntity.cpp \
           Map1Entity.cpp \
           FileMapEntity.cpp \
           MissileEntity.cpp \
           MissileLauncherMobEntity.cpp \
           ParticleGeneratorEntity.cpp \
           TimerEntity.cpp \
           LuaMissileEntity.cpp \


HEADERS += \
            ADamageInteraction.hpp \
            EnemyDamageInteraction.hpp \
            FriendlyDamageInteraction.hpp \
            BonusInteraction.hpp \
            ForceAttachInteraction.hpp \
            ForceControlInteraction.hpp \
            ForceFireInteraction.hpp \
            ShieldInteraction.hpp \
            RepulseInteraction.hpp \
            ShipEntity.hpp \
            WallEntity.hpp \
            WallGeneratorEntity.hpp \
            MapEntity.hpp \
            EnduranceMap1Entity.hpp \
            MonsterEntity.hpp \
            WeakMobEntity.hpp \
            LittleRobotMobEntity.hpp \
            MonsterInteraction.hpp \
            ShipInteraction.hpp \
            WallInteraction.hpp \
            MonsterGeneratorEntity.hpp \
            BulletEntity.hpp \
            FriendlyBulletEntity.hpp \
            EnemyBulletEntity.hpp \
            GarbageSpawnerEntity.hpp \
            GarbageEntity.hpp \
            TriggerInteraction.hpp \
            ForceUpgradeInteraction.hpp \
            ForceDowngradeInteraction.hpp \
            BonusEntity.hpp \
            BoingLaserEntity.hpp \
            ExplosiveEntity.hpp \
            FlameEntity.hpp \
            Boss1Entity.hpp \
            Boss1Node.hpp \
            BossBulletEntity.hpp \
            BgTileEntity.hpp \
            BonusCarrierMobEntity.hpp \

SOURCES += \
            ADamageInteraction.cpp \
            EnemyDamageInteraction.cpp \
            FriendlyDamageInteraction.cpp \
            BonusInteraction.cpp \
            ForceAttachInteraction.cpp \
            ForceControlInteraction.cpp \
            ForceFireInteraction.cpp \
            ShieldInteraction.cpp \
            RepulseInteraction.cpp \
            ShipEntity.cpp \
            WallEntity.cpp \
            WallGeneratorEntity.cpp \
            MapEntity.cpp \
            EnduranceMap1Entity.cpp \
            MonsterEntity.cpp \
            WeakMobEntity.cpp \
            LittleRobotMobEntity.cpp \
            MonsterInteraction.cpp \
            ShipInteraction.cpp \
            WallInteraction.cpp \
            MonsterGeneratorEntity.cpp \
            BulletEntity.cpp \
            FriendlyBulletEntity.cpp \
            EnemyBulletEntity.cpp \
            GarbageSpawnerEntity.cpp \
            GarbageEntity.cpp \
            TriggerInteraction.cpp \
            ForceUpgradeInteraction.cpp \
            ForceDowngradeInteraction.cpp \
            BonusEntity.cpp \
            BoingLaserEntity.cpp \
            ExplosiveEntity.cpp \
            FlameEntity.cpp \
            Boss1Entity.cpp \
            Boss1Node.cpp \
            BossBulletEntity.cpp \
            BgTileEntity.cpp \
            BonusCarrierMobEntity.cpp \


