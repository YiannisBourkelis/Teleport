QT += quick

CONFIG += c++14
CONFIG -= rtti

#exceptions_off

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        ../../shared/byte_functions.cpp \
        ../../shared/socket_utils.cpp \
        client_engine.cpp \
        client_session.cpp \
        main.cpp \
        protocol.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    ../../shared/byte_functions.h \
    ../../shared/payload_types.h \
    ../../shared/socket_utils.h \
    client_engine.h \
    client_session.h \
    client_state.h \
    protocol.h \
    shared_context.h \
    shared_globals.h

linux:LIBS += -L/usr/lib/x86_64-linux-gnu/ -lboost_system

mac:INCLUDEPATH += "/usr/local/Cellar/boost/1.72.0_1/include"
mac:LIBS += -L/usr/local/Cellar/boost/1.72.0_1/lib -lboost_system
