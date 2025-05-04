QT += core gui sql printsupport widgets charts quick quickwidgets location positioning serialport network pdf

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    arduino.cpp \
    centre.cpp \
    chatbotia.cpp \
    connection.cpp \
    deplome.cpp \
    dialogid.cpp \                    # ✅ Ajouté : implémentation de DialogID
    emaildialog.cpp \
    employe.cpp \
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
    piechartwidget.cpp \
    recommendation.cpp \
    tmpdialog.cpp \
    todolist.cpp

HEADERS += \
    arduino.h \
    centre.h \
    chatbotia.h \
    connection.h \
    deplome.h \
    dialogid.h \
    emaildialog.h \
    employe.h \
    examen.h \
    fenetrecontrolerfid.h \
    fenetrescanbadges.h \
    fenetresignatures.h \
    fenetrestatsf.h \
    formation.h \
    historiquebadges.h \
    logdialog.h \
    mainwindow.h \
    piechartwidget.h \
    recommendation.h \
    tmpdialog.h \
    todolist.h

FORMS += \
    chatbotia.ui \
    deplome.ui \
    dialogid.ui \
    emaildialog.ui \
    fenetrecontrolerfid.ui \
    fenetrescanbadges.ui \
    fenetresignatures.ui \
    fenetrestatsf.ui \
    historiquebadges.ui \
    logdialog.ui \
    mainwindow.ui \
    tmpdialog.ui \
    todolist.ui

RESOURCES += \
    PERS.qrc \
    resources.qrc

# Default rules for deployment
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
