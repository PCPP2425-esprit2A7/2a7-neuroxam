/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSMainWindowENDCLASS = QtMocHelpers::stringData(
    "MainWindow",
    "loadStudents",
    "",
    "sortBy",
    "onAddStudent",
    "onUpdateStudent",
    "onDeleteStudent",
    "onSortStudents",
    "criteria",
    "onSearch",
    "onShowStats",
    "onSavePDF",
    "onSaveStudentPDF",
    "onBrowseImage",
    "onLoadStudentDetails",
    "studentId",
    "clearFields",
    "onOpenChatDialog"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMainWindowENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   98,    2, 0x08,    1 /* Private */,
       1,    0,  101,    2, 0x28,    3 /* Private | MethodCloned */,
       4,    0,  102,    2, 0x08,    4 /* Private */,
       5,    0,  103,    2, 0x08,    5 /* Private */,
       6,    0,  104,    2, 0x08,    6 /* Private */,
       7,    1,  105,    2, 0x08,    7 /* Private */,
       9,    0,  108,    2, 0x08,    9 /* Private */,
      10,    0,  109,    2, 0x08,   10 /* Private */,
      11,    0,  110,    2, 0x08,   11 /* Private */,
      12,    0,  111,    2, 0x08,   12 /* Private */,
      13,    0,  112,    2, 0x08,   13 /* Private */,
      14,    1,  113,    2, 0x08,   14 /* Private */,
      16,    0,  116,    2, 0x08,   16 /* Private */,
      17,    0,  117,    2, 0x08,   17 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSMainWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMainWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMainWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'loadStudents'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'loadStudents'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onAddStudent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onUpdateStudent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onDeleteStudent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onSortStudents'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'onSearch'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onShowStats'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onSavePDF'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onSaveStudentPDF'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onBrowseImage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onLoadStudentDetails'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'clearFields'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onOpenChatDialog'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->loadStudents((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->loadStudents(); break;
        case 2: _t->onAddStudent(); break;
        case 3: _t->onUpdateStudent(); break;
        case 4: _t->onDeleteStudent(); break;
        case 5: _t->onSortStudents((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 6: _t->onSearch(); break;
        case 7: _t->onShowStats(); break;
        case 8: _t->onSavePDF(); break;
        case 9: _t->onSaveStudentPDF(); break;
        case 10: _t->onBrowseImage(); break;
        case 11: _t->onLoadStudentDetails((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 12: _t->clearFields(); break;
        case 13: _t->onOpenChatDialog(); break;
        default: ;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMainWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
