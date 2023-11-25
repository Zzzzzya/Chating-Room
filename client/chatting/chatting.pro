QT       += core gui network
LIBS += -lWs2_32

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addapply.cpp \
    addfrient.cpp \
    craetgroupname.cpp \
    creatgroup.cpp \
    creatsuc.cpp \
    friendchat.cpp \
    groupchat.cpp \
    groupchatting.cpp \
    login.cpp \
    main.cpp \
    mysocket.cpp \
    register.cpp \
    register_success.cpp \
    signalchating.cpp \
    usersql.cpp

HEADERS += \
    addapply.h \
    addfrient.h \
    craetgroupname.h \
    creatgroup.h \
    creatsuc.h \
    friendchat.h \
    groupchat.h \
    groupchatting.h \
    login.h \
    mysocket.h \
    register.h \
    register_success.h \
    signalchating.h \
    usersql.h

FORMS += \
    addapply.ui \
    addfrient.ui \
    craetgroupname.ui \
    creatgroup.ui \
    creatsuc.ui \
    friendchat.ui \
    groupchat.ui \
    groupchatting.ui \
    login.ui \
    register.ui \
    register_success.ui \
    signalchating.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
