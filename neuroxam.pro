QT += core gui sql printsupport charts quick quickwidgets location positioning serialport widgets

INCLUDEPATH += $$PWD/center
INCLUDEPATH += $$PWD/materiel
INCLUDEPATH += $$PWD/examen
INCLUDEPATH += $$PWD/employe
INCLUDEPATH += $$PWD/formation



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    centre/arduino.cpp \
    centre/centre.cpp \
    centre/centrewindow.cpp \
    centre/piechartwidget.cpp \
    centre/recommendation.cpp \
    centre/tmpdialog.cpp \
    employe/employe.cpp \
    employe/employewindow.cpp \
    examen/emaildialog.cpp \
    examen/examen.cpp \
    examen/examenwindow.cpp \
    formation/chatbotia.cpp \
    formation/deplome.cpp \
    formation/dialogid.cpp \
    formation/fenetrecontrolerfid.cpp \
    formation/fenetrescanbadges.cpp \
    formation/fenetresignatures.cpp \
    formation/fenetrestatsf.cpp \
    formation/formation.cpp \
    formation/formationwindow.cpp \
    formation/historiquebadges.cpp \
    formation/qrcodegen.cpp \
    formation/todolist.cpp \
    materiel/materielManager.cpp \
    materiel/materielwindow.cpp \
    materiel/optimization.cpp \
    materiel/allocationdialog.cpp \
    database.cpp \
    logdialog.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    centre/arduino.h \
    centre/centre.h \
    centre/centrewindow.h \
    centre/piechartwidget.h \
    centre/recommendation.h \
    centre/tmpdialog.h \
    employe/employe.h \
    employe/employewindow.h \
    examen/emaildialog.h \
    examen/examen.h \
    examen/examenwindow.h \
    formation/chatbotia.h \
    formation/deplome.h \
    formation/dialogid.h \
    formation/fenetrecontrolerfid.h \
    formation/fenetrescanbadges.h \
    formation/fenetresignatures.h \
    formation/fenetrestatsf.h \
    formation/formation.h \
    formation/formationwindow.h \
    formation/historiquebadges.h \
    formation/qrcodegen.hpp \
    formation/todolist.h \
    materiel/materiel.h \
    materiel/materielManager.h \
    materiel/materielwindow.h \
    materiel/optimization.h \
    materiel/allocationdialog.h \
    database.h \
    logdialog.h \
    mainwindow.h

FORMS += \
    centre/centrewindow.ui \
    centre/tmpdialog.ui \
    employe/employewindow.ui \
    examen/emaildialog.ui \
    examen/examenwindow.ui \
    formation/chatbotia.ui \
    formation/deplome.ui \
    formation/dialogid.ui \
    formation/fenetrecontrolerfid.ui \
    formation/fenetrescanbadges.ui \
    formation/fenetresignatures.ui \
    formation/fenetrestatsf.ui \
    formation/formationwindow.ui \
    formation/historiquebadges.ui \
    formation/todolist.ui \
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
