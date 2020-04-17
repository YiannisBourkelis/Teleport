TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        ../../shared/payload_types.cpp \
        globals.cpp \
        main.cpp \
        server.cpp \
        session.cpp

HEADERS += \
    ../../shared/payload_types.h \
    globals.h \
    server.h \
    session.h

mac:INCLUDEPATH += "/usr/local/Cellar/boost/1.72.0_1/include"
mac:LIBS += -L/usr/local/Cellar/boost/1.72.0_1/lib -lboost_system
