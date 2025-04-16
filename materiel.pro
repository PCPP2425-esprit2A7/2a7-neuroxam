QT += core gui
QT += sql
QT += core gui widgets
QT += charts



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    allocationdialog.cpp \
    database.cpp \
    main.cpp \
    mainwindow.cpp \
    materielManager.cpp

HEADERS += \
    allocationdialog.h \
    database.h \
    mainwindow.h \
    materiel.h \
    materielManager.h

FORMS += \
    allocationdialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc \
    resources.qrc \
    resources.qrc

DISTFILES += \
    image 1.jpg \
    image 2.png \
    image 3.png \
    image 4.png \
    image 5.png \
    image 6.png \
    image 7.png \
    image 8.png \
    resources/background.png \
    resources/background.png \
    resources/click.wav \
    resources/click.wav \
    resources/image_2025-01-29_201537391-removebg-preview.png \
    resources/image_2025-01-29_201537391-removebg-preview.png \
    resources/logo.png \
    resources/logo.png
