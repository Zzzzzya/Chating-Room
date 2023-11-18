QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addapply.cpp \
    addfrient.cpp \
    creatgroup.cpp \
    creatsuc.cpp \
    friendchat.cpp \
    groupchat.cpp \
    login.cpp \
    main.cpp \
    online.cpp \
    register.cpp \
    register_success.cpp

HEADERS += \
    addapply.h \
    addfrient.h \
    creatgroup.h \
    creatsuc.h \
    friendchat.h \
    groupchat.h \
    login.h \
    online.h \
    register.h \
    register_success.h

FORMS += \
    addapply.ui \
    addfrient.ui \
    creatgroup.ui \
    creatsuc.ui \
    friendchat.ui \
    groupchat.ui \
    login.ui \
    register.ui \
    register_success.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
