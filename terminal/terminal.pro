TEMPLATE = app
TARGET = terminal
DEPENDPATH += src ../common
INCLUDEPATH += src ../common

CONFIG += warn_on qt moc uic

QMAKE_CXXFLAGS_DEBUG += -DDEBUG

unix {
    QMAKE_CXXFLAGS = -Wall -Wextra -include stdint.h -include cstdlib
    CONFIG += link_pkgconfig
    PKGCONFIG += lua5.1 luabind
}

win32 {
    QMAKE_CXXFLAGS = "/FI Types.hpp" "/Fo.\\objs\\$(ConfigurationName)\\" "/Fd.\\objs\\$(ConfigurationName)\\"
    INCLUDEPATH += ../windows
    LIBS += -lWs2_32 -llua51 -lluabind
}

LIBS += -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
QT += network
RESOURCES += ui/resources.qrc

HEADERS += src/Terminal.hpp \
           src/UpdaterWindow.hpp \
           src/ConnectionWindow.hpp \
           src/INetwork.hpp \
           src/QtNetwork.hpp \
           src/TcpPacketManager.hpp \
           src/IGameView.hpp \
           src/SfmlGameView.hpp \
           src/SfmlRenderer.hpp \
           src/EventManager.hpp \
           src/IItem.hpp \
           src/SpriteItem.hpp \
           src/SoundItem.hpp \
           src/SfmlAnimation.hpp \
           src/SfmlSound.hpp \
           src/LuaFile.hpp \
           ../common/Log.hpp \
           ../common/Packet.hpp \
           ../common/String.hpp

FORMS += ui/connection.ui \
         ui/updater.ui

SOURCES += src/main.cpp \
           src/Terminal.cpp \
           src/UpdaterWindow.cpp \
           src/ConnectionWindow.cpp \
           src/QtNetwork.cpp \
           src/TcpPacketManager.cpp \
           src/SfmlGameView.cpp \
           src/SfmlRenderer.cpp \
           src/EventManager.cpp \
           src/SpriteItem.cpp \
           src/SoundItem.cpp \
           src/SfmlAnimation.cpp \
           src/SfmlSound.cpp \
           src/LuaFile.cpp \
           ../common/Packet.cpp \
           ../common/String.cpp

