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
    dialog.cpp \
    emaildialog.cpp \
    examen.cpp \
    main.cpp \
    mainwindow.cpp \
    piechartwidget.cpp \
    recommendation.cpp

HEADERS += \
    arduino.h \
    centre.h \
    connection.h \
    dialog.h \
    emaildialog.h \
    examen.h \
    mainwindow.h \
    piechartwidget.h \
    recommendation.h

FORMS += \
    dialog.ui \
    emaildialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
