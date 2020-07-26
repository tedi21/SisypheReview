TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

DEFINES += SQLITE_ENABLE_FTS3 \
           SQLITE_ENABLE_FTS3_PARENTHESIS


SOURCES += \
    ../shell.c \
    ../../sqlite3.c

INCLUDEPATH += \
    ../..

LIBS += -lpthread -ldl

