#-------------------------------------------------
#
# Project created by QtCreator 2019-04-10T21:35:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LPM_GUI
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

CONFIG += c++14

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    steam_user_list.cpp \
    steam_user_list_notindatabase.cpp \
    instalacja_programu.cpp \
    get_string.cpp \
    getwidestring.cpp \
    show_password.cpp

HEADERS += \
        mainwindow.h \
    steam_user_list.h \
    utility_v2.h \
    steam_user_list_notindatabase.h \
    instalacja.h \
    instalacja_programu.h \
    get_string.h \
    getwidestring.h \
    show_password.h \
    lpm_config.h \
    lpm_password.h \
    lpm_utility.h \
    lpm_users.h

FORMS += \
    steam_user_list.ui \
    steam_user_list_notindatabase.ui \
    instalacja_programu.ui \
    mainwindow.ui \
    get_string.ui \
    getwidestring.ui \
    show_password.ui

RC_FILE = LPM_Icon.rc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
