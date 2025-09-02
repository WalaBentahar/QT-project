/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QtNetwork/QSslError>
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
    "showClientsPage",
    "",
    "showCommandesPage",
    "showStatisticsPage",
    "addClient",
    "editClient",
    "deleteClient",
    "searchClients",
    "refreshClientsTable",
    "onClientTableContextMenu",
    "pos",
    "addCommande",
    "editCommande",
    "deleteCommande",
    "refreshCommandesTable",
    "onCommandeTableContextMenu",
    "exportCommandesToPDF",
    "searchCommandes",
    "clearSearchCommandes",
    "refreshStatistics",
    "onClientTableDoubleClick",
    "row",
    "column",
    "onCommandeTableDoubleClick",
    "sortClients",
    "sortCommandes",
    "onTrayIconActivated",
    "QSystemTrayIcon::ActivationReason",
    "reason",
    "showMainWindow",
    "exitApplication",
    "onEmailSent",
    "success",
    "message"
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
      26,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  170,    2, 0x08,    1 /* Private */,
       3,    0,  171,    2, 0x08,    2 /* Private */,
       4,    0,  172,    2, 0x08,    3 /* Private */,
       5,    0,  173,    2, 0x08,    4 /* Private */,
       6,    0,  174,    2, 0x08,    5 /* Private */,
       7,    0,  175,    2, 0x08,    6 /* Private */,
       8,    0,  176,    2, 0x08,    7 /* Private */,
       9,    0,  177,    2, 0x08,    8 /* Private */,
      10,    1,  178,    2, 0x08,    9 /* Private */,
      12,    0,  181,    2, 0x08,   11 /* Private */,
      13,    0,  182,    2, 0x08,   12 /* Private */,
      14,    0,  183,    2, 0x08,   13 /* Private */,
      15,    0,  184,    2, 0x08,   14 /* Private */,
      16,    1,  185,    2, 0x08,   15 /* Private */,
      17,    0,  188,    2, 0x08,   17 /* Private */,
      18,    0,  189,    2, 0x08,   18 /* Private */,
      19,    0,  190,    2, 0x08,   19 /* Private */,
      20,    0,  191,    2, 0x08,   20 /* Private */,
      21,    2,  192,    2, 0x08,   21 /* Private */,
      24,    2,  197,    2, 0x08,   24 /* Private */,
      25,    0,  202,    2, 0x08,   27 /* Private */,
      26,    0,  203,    2, 0x08,   28 /* Private */,
      27,    1,  204,    2, 0x08,   29 /* Private */,
      30,    0,  207,    2, 0x08,   31 /* Private */,
      31,    0,  208,    2, 0x08,   32 /* Private */,
      32,    2,  209,    2, 0x08,   33 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   22,   23,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   22,   23,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 28,   29,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString,   33,   34,

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
        // method 'showClientsPage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showCommandesPage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showStatisticsPage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'addClient'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'editClient'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'deleteClient'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'searchClients'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'refreshClientsTable'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onClientTableContextMenu'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QPoint &, std::false_type>,
        // method 'addCommande'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'editCommande'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'deleteCommande'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'refreshCommandesTable'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onCommandeTableContextMenu'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QPoint &, std::false_type>,
        // method 'exportCommandesToPDF'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'searchCommandes'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'clearSearchCommandes'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'refreshStatistics'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onClientTableDoubleClick'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onCommandeTableDoubleClick'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'sortClients'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'sortCommandes'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onTrayIconActivated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QSystemTrayIcon::ActivationReason, std::false_type>,
        // method 'showMainWindow'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'exitApplication'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onEmailSent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->showClientsPage(); break;
        case 1: _t->showCommandesPage(); break;
        case 2: _t->showStatisticsPage(); break;
        case 3: _t->addClient(); break;
        case 4: _t->editClient(); break;
        case 5: _t->deleteClient(); break;
        case 6: _t->searchClients(); break;
        case 7: _t->refreshClientsTable(); break;
        case 8: _t->onClientTableContextMenu((*reinterpret_cast< std::add_pointer_t<QPoint>>(_a[1]))); break;
        case 9: _t->addCommande(); break;
        case 10: _t->editCommande(); break;
        case 11: _t->deleteCommande(); break;
        case 12: _t->refreshCommandesTable(); break;
        case 13: _t->onCommandeTableContextMenu((*reinterpret_cast< std::add_pointer_t<QPoint>>(_a[1]))); break;
        case 14: _t->exportCommandesToPDF(); break;
        case 15: _t->searchCommandes(); break;
        case 16: _t->clearSearchCommandes(); break;
        case 17: _t->refreshStatistics(); break;
        case 18: _t->onClientTableDoubleClick((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 19: _t->onCommandeTableDoubleClick((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 20: _t->sortClients(); break;
        case 21: _t->sortCommandes(); break;
        case 22: _t->onTrayIconActivated((*reinterpret_cast< std::add_pointer_t<QSystemTrayIcon::ActivationReason>>(_a[1]))); break;
        case 23: _t->showMainWindow(); break;
        case 24: _t->exitApplication(); break;
        case 25: _t->onEmailSent((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
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
        if (_id < 26)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 26;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 26)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 26;
    }
    return _id;
}
QT_WARNING_POP
