QT += core gui sql printsupport charts quick quickwidgets location positioning serialport widgets

INCLUDEPATH += $$PWD/materiel




greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    materiel/materielManager.cpp \
    materiel/materielwindow.cpp \
    materiel/optimization.cpp \
    materiel/allocationdialog.cpp \
    database.cpp \
    logdialog.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    materiel/materiel.h \
    materiel/materielManager.h \
    materiel/materielwindow.h \
    materiel/optimization.h \
    materiel/allocationdialog.h \
    database.h \
    logdialog.h \
    mainwindow.h

FORMS += \
    materiel/allocationdialog.ui \
    materiel/materielwindow.ui \
    materiel/optimization.ui \
    logdialog.ui \
    mainwindow.ui

RESOURCES += \
    PERS.qrc \
    resources.qrc

DISTFILES += \
    employe/send_email.py \
    examen/send_email.py \
    image 1.jpg \
    image 2.png \
    image 3.png \
    image 4.png \
    image 5.png \
    image 6.png \
    image 7.png \
    image 8.png \
    map.qml \
    resources/475038336_657821386805867_9178055062394887346_n__1_-removebg-preview.png \
    resources/add-user.png \
    resources/back.jpeg \
    resources/background.png \
    resources/circle.png \
    resources/click.wav \
    resources/delete.png \
    resources/email.png \
    resources/glass.png \
    resources/image-removebg-preview (5).png \
    resources/image_2025-01-29_201537391-removebg-preview.png \
    resources/logo.png \
    resources/pers.png \
    resources/profile.png \
    verify_face.py

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
