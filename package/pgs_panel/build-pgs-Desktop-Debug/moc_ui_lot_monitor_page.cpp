/****************************************************************************
** Meta object code from reading C++ file 'ui_lot_monitor_page.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ui_lot_monitor_page.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ui_lot_monitor_page.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui_lot_monitor_page_t {
    QByteArrayData data[8];
    char stringdata0[114];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui_lot_monitor_page_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui_lot_monitor_page_t qt_meta_stringdata_ui_lot_monitor_page = {
    {
QT_MOC_LITERAL(0, 0, 19), // "ui_lot_monitor_page"
QT_MOC_LITERAL(1, 20, 14), // "camera_clicked"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 14), // "combo_selected"
QT_MOC_LITERAL(4, 51, 5), // "index"
QT_MOC_LITERAL(5, 57, 20), // "combo_selected_level"
QT_MOC_LITERAL(6, 78, 17), // "page_prev_clicked"
QT_MOC_LITERAL(7, 96, 17) // "page_next_clicked"

    },
    "ui_lot_monitor_page\0camera_clicked\0\0"
    "combo_selected\0index\0combo_selected_level\0"
    "page_prev_clicked\0page_next_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui_lot_monitor_page[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x0a /* Public */,
       3,    1,   40,    2, 0x0a /* Public */,
       5,    1,   43,    2, 0x0a /* Public */,
       6,    0,   46,    2, 0x0a /* Public */,
       7,    0,   47,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ui_lot_monitor_page::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ui_lot_monitor_page *_t = static_cast<ui_lot_monitor_page *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->camera_clicked(); break;
        case 1: _t->combo_selected((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->combo_selected_level((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->page_prev_clicked(); break;
        case 4: _t->page_next_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject ui_lot_monitor_page::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ui_lot_monitor_page.data,
      qt_meta_data_ui_lot_monitor_page,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ui_lot_monitor_page::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui_lot_monitor_page::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui_lot_monitor_page.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ui_lot_monitor_page::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
