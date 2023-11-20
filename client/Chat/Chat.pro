QT += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    add_friend.cpp \
    client.cpp \
    l_friend.cpp \
    l_group.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    new_friend.cpp \
    regis.cpp \
    set_group.cpp
    login.cpp
    regis.cpp
    l_friend.cpp
    l_group.cpp
    add_friend.cpp
    set_group.cpp
    new_friend.cpp
    client.cpp
HEADERS += \
    add_friend.h \
    client.h \
    l_friend.h \
    l_group.h \
    login.h \
    mainwindow.h \
    new_friend.h \
    regis.h \
    set_group.h
    login.h
    regis.h
    l_friend.h
    l_group.h
    add_friend.h
    set_group.h
    new_friend.h
    client.h

FORMS += \
    add_friend.ui \
    l_friend.ui \
    l_group.ui \
    login.ui \
    mainwindow.ui \
    new_friend.ui \
    regis.ui \
    set_group.ui
    login.ui
    regis.ui
    l_friend.ui
    l_group.ui
    add_friend.ui
    set_group.ui
    new_friend.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
