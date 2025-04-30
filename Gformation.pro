QT       += core gui sql printsupport widgets charts network pdf

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
TEMPLATE = app
TARGET = Gformation
QT += serialport
QT += sql

# Fichiers source (.cpp)
SOURCES += \
    fenetrecontrolerfid.cpp \
    fenetrescanbadges.cpp \
    fenetresignatures.cpp \
    historiquebadges.cpp \
    main.cpp \
    mainwindow.cpp \
    chatbotia.cpp \
    connection.cpp \
    dialogid.cpp \
    dialogrecherche.cpp \
    formation.cpp \
    qrcodegen.cpp \
    googleuploader.cpp \
    todolist.cpp

# Fichiers en-tête (.h)
HEADERS += \
    fenetrecontrolerfid.h \
    fenetrescanbadges.h \
    fenetresignatures.h \
    historiquebadges.h \
    mainwindow.h \
    chatbotia.h \
    connection.h \
    dialogid.h \
    dialogrecherche.h \
    formation.h \
    googleuploader.h \
    qrcodegen.hpp \
    todolist.h

# Interfaces utilisateur (.ui)
FORMS += \
    fenetrecontrolerfid.ui \
    fenetrescanbadges.ui \
    historiquebadges.ui \
    mainwindow.ui \
    chatbotia.ui \
    dialogid.ui \
    dialogrecherche.ui \
    fenetresignatures.ui \
    todolist.ui

# Ressources (icônes/images)
RESOURCES += resources.qrc

# Déploiement Unix/QNX
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
