#-------------------------------------------------
#
# Project created by QtCreator 2019-04-19T14:48:39
#
#-------------------------------------------------

QT       += core gui network multimedia sql


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = full_link_monitoring
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        window.cpp \
    UI/main/linkmodel.cpp \
    UI/main/tittle.cpp \
    UI/main/sourcemodel.cpp \
    UI/main/radiomodel.cpp \
    UI/main/forcemodel.cpp \
    data/global.cpp \
    data/audio/player.cpp \
    data/audio/processmanage.cpp \
    data/audio/receivedata.cpp \
    data/alarm/reaudiodata.cpp \
    UI/popup/globalset.cpp \
    data/sql/sqlite.cpp \
    UI/popup/logquery.cpp \
    UI/popup/mp3player.cpp \
    UI/popup/alarmset/timeline.cpp \
    UI/popup/alarmset/timeday.cpp \
    UI/popup/alarmset/timeweek.cpp \
    UI/popup/alarmset/timelink.cpp \
    UI/popup/alarmset/gatelink.cpp

HEADERS += \
        window.h \
    UI/main/linkmodel.h \
    UI/main/tittle.h \
    UI/main/sourcemodel.h \
    UI/main/radiomodel.h \
    UI/main/forcemodel.h \
    data/global.h \
    data/audio/player.h \
    data/audio/processmanage.h \
    data/audio/receivedata.h \
    data/alarm/reaudiodata.h \
    UI/popup/globalset.h \
    data/sql/sqlite.h \
    UI/popup/logquery.h \
    UI/popup/mp3player.h \
    UI/popup/alarmset/timeline.h \
    UI/popup/alarmset/timeday.h \
    UI/popup/alarmset/timeweek.h \
    UI/popup/alarmset/timelink.h \
    UI/popup/alarmset/gatelink.h

FORMS += \
        window.ui \
    UI/main/linkmodel.ui \
    UI/main/tittle.ui \
    UI/main/sourcemodel.ui \
    UI/main/radiomodel.ui \
    UI/main/forcemodel.ui \
    UI/popup/globalset.ui \
    UI/popup/logquery.ui \
    UI/popup/mp3player.ui \
    UI/popup/alarmset/timeline.ui \
    UI/popup/alarmset/timeday.ui \
    UI/popup/alarmset/timeweek.ui \
    UI/popup/alarmset/timelink.ui \
    UI/popup/alarmset/gatelink.ui
INCLUDEPATH += $$PWD/sdk
CONFIG(release, debug|release){
LIBS        += -L$$PWD/sdk/ -lquc
} else {
unix {LIBS  += -L$$PWD/sdk/ -lquc}
else {LIBS  += -L$$PWD/sdk/ -lqucd}
}
RC_ICONS = ggd512.ico
RESOURCES += \
    img.qrc
