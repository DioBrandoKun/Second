QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG   += rtti
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Accept.cpp \
    ICounter.cpp \
    dialog.cpp \
    main.cpp \
    memento.cpp \
    window.cpp

HEADERS += \
    Accept.h \
    IComp.h \
    ICounter.h \
    dialog.h \
    memento.h \
    window.h

FORMS += \
    dialog.ui \
    window.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
