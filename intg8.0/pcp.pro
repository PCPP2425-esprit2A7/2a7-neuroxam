QT += core gui sql printsupport widgets charts quick quickwidgets location positioning serialport network pdf

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    allocationdialog.cpp \
    arduino.cpp \
    centre.cpp \
    chatbotia.cpp \
    chatbotservice.cpp \
    chatdialog.cpp \
    connection.cpp \
    deplome.cpp \
    dialogid.cpp \
    dialogrecherche.cpp \
    emaildialog.cpp \
    employe.cpp \
    etudiant.cpp \
    etudiantservice.cpp \
    examen.cpp \
    fenetrecontrolerfid.cpp \
    fenetrescanbadges.cpp \
    fenetresignatures.cpp \
    fenetrestatsf.cpp \
    formation.cpp \
    historiquebadges.cpp \
    logdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    materielmanager.cpp \
    optimization.cpp \
    piechartwidget.cpp \
    recommendation.cpp \
    tmpdialog.cpp \
    todolist.cpp

HEADERS += \
    allocationdialog.h \
    arduino.h \
    centre.h \
    chatbotia.h \
    chatbotservice.h \
    chatdialog.h \
    connection.h \
    deplome.h \
    dialogid.h \
    dialogrecherche.h \
    emaildialog.h \
    employe.h \
    etudiant.h \
    etudiantservice.h \
    examen.h \
    fenetrecontrolerfid.h \
    fenetrescanbadges.h \
    fenetresignatures.h \
    fenetrestatsf.h \
    formation.h \
    historiquebadges.h \
    logdialog.h \
    mainwindow.h \
    materiel.h \
    materielmanager.h \
    optimization.h \
    piechartwidget.h \
    recommendation.h \
    tmpdialog.h \
    todolist.h

FORMS += \
    allocationdialog.ui \
    chatbotia.ui \
    deplome.ui \
    dialogid.ui \
    dialogrecherche.ui \
    emaildialog.ui \
    fenetrecontrolerfid.ui \
    fenetrescanbadges.ui \
    fenetresignatures.ui \
    fenetrestatsf.ui \
    historiquebadges.ui \
    logdialog.ui \
    mainwindow.ui \
    optimization.ui \
    tmpdialog.ui \
    todolist.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    PERS.qrc \
    resources.qrc
