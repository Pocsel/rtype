
message(" **** Configuration: " + $$CONFIG)

CONFIG += warn_on
TEMPLATE = subdirs
SUBDIRS += terminal/terminal.pro \
           server/server.pro \
           server/games/chicken/chicken.pro \
           server/games/mainmenu/mainmenu.pro \
           server/games/bomberman/bomberman.pro \
           server/games/rtype/rtype.pro \
           server/games/blobby/blobby.pro \

