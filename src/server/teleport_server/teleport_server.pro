TEMPLATE = app
CONFIG += console c++14 thread
CONFIG -= rtti
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        ../../shared/byte_functions.cpp \
        ../../shared/socket_utils.cpp \
        client.cpp \
        clients.cpp \
        globals.cpp \
        main.cpp \
        server.cpp \
        server_protocol.cpp \
        session.cpp

HEADERS += \
    ../../shared/byte_functions.h \
    ../../shared/payload_types.h \
    ../../shared/socket_utils.h \
    client.h \
    clients.h \
    globals.h \
    server.h \
    server_protocol.h \
    session.h

linux:LIBS += -L/usr/lib/x86_64-linux-gnu/ -lboost_system

mac:INCLUDEPATH += "/usr/local/Cellar/boost/1.72.0_1/include"
mac:LIBS += -L/usr/local/Cellar/boost/1.72.0_1/lib -lboost_system
