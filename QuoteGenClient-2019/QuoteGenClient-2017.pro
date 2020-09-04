#-------------------------------------------------
#
# Project created by QtCreator 2017-04-07T10:53:25
#
#-------------------------------------------------

QT += core gui sql printsupport \
    quick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QuoteGenClient-2017
TEMPLATE = app
RC_FILE = QuoteGenClient-2017.rc

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    customerinfo.cpp \
        mainwindow.cpp \
    pricesidebar.cpp \
    quotedbmanager.cpp \
    quotedbpricemanager.cpp \
    quotepdfmanager.cpp \
    authentication.cpp \
    quotestatus.cpp \
    encryptionhandler.cpp

HEADERS  += mainwindow.h \
    customerinfo.h \
    pricesidebar.h \
    quotedbmanager.h \
    quotedbpricemanager.h \
    quotepdfmanager.h \
    quotepdfmanager.h \
    authentication.h \
    quotestatus.h \
    encryptionhandler.h

FORMS    += mainwindow.ui \
    authentication.ui \
    customerinfo.ui \
    pricesidebar.ui \
    quotestatus.ui

RESOURCES += \
    resources.qrc

DISTFILES += \
    simplelogo2.jpg

OTHER_FILES +=
