QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    attackresult.cpp \
    battle.cpp \
    battlefield.cpp \
    choicearmy.cpp \
    choicesquad.cpp \
    choiceweapon.cpp \
    editfile.cpp \
    fight.cpp \
    fillsquad.cpp \
    main.cpp \
    mainwindow.cpp \
    random.cpp \
    squad.cpp \
    unit.cpp \
    weapon.cpp

HEADERS += \
    attackresult.h \
    battle.h \
    battlefield.h \
    choicearmy.h \
    choicesquad.h \
    choiceweapon.h \
    editfile.h \
    fight.h \
    fillsquad.h \
    mainwindow.h \
    random.h \
    squad.h \
    unit.h \
    weapon.h

FORMS += \
    attackresult.ui \
    battlefield.ui \
    choicearmy.ui \
    choicesquad.ui \
    choiceweapon.ui \
    fillsquad.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
