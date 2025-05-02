QT += core gui sql printsupport widgets charts quick quickwidgets location positioning serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arduino.cpp \
    centre.cpp \
    connection.cpp \
    emaildialog.cpp \
    employe.cpp \
    examen.cpp \
    logdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    piechartwidget.cpp \
    recommendation.cpp \
    tmpdialog.cpp

HEADERS += \
    arduino.h \
    centre.h \
    connection.h \
    emaildialog.h \
    employe.h \
    examen.h \
    logdialog.h \
    mainwindow.h \
    piechartwidget.h \
    recommendation.h \
    tmpdialog.h

FORMS += \
    emaildialog.ui \
    logdialog.ui \
    mainwindow.ui \
    tmpdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    PERS.qrc \
    resources.qrc
