TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG+=sdk_no_version_check

SOURCES += \
        board.c \
        game.c \
        main.c \
        protocol.c \
        settings.c

HEADERS += \
    board.h \
    game.h \
    header.h \
    protocol.h \
    settings.h
