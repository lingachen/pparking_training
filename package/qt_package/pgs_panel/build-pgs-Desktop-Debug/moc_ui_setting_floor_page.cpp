/****************************************************************************
** Meta object code from reading C++ file 'ui_setting_floor_page.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ui_setting_floor_page.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ui_setting_floor_page.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui_setting_floor_page_t {
    QByteArrayData data[10];
    char stringdata0[132];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui_setting_floor_page_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui_setting_floor_page_t qt_meta_stringdata_ui_setting_floor_page = {
    {
QT_MOC_LITERAL(0, 0, 21), // "ui_setting_floor_page"
QT_MOC_LITERAL(1, 22, 16), // "btn_load_clicked"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 15), // "btn_add_clicked"
QT_MOC_LITERAL(4, 56, 15), // "btn_del_clicked"
QT_MOC_LITERAL(5, 72, 15), // "btn_upd_clicked"
QT_MOC_LITERAL(6, 88, 15), // "btn_qry_clicked"
QT_MOC_LITERAL(7, 104, 19), // "info_record_clicked"
QT_MOC_LITERAL(8, 124, 3), // "row"
QT_MOC_LITERAL(9, 128, 3) // "col"

    },
    "ui_setting_floor_page\0btn_load_clicked\0"
    "\0btn_add_clicked\0btn_del_clicked\0"
    "btn_upd_clicked\0btn_qry_clicked\0"
    "info_record_clicked\0row\0col"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui_setting_floor_page[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x0a /* Public */,
       3,    0,   45,    2, 0x0a /* Public */,
       4,    0,   46,    2, 0x0a /* Public */,
       5,    0,   47,    2, 0x0a /* Public */,
       6,    0,   48,    2, 0x0a /* Public */,
       7,    2,   49,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    8,    9,

       0        // eod
};

void ui_setting_floor_page::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ui_setting_floor_page *_t = static_cast<ui_setting_floor_page *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->btn_load_clicked(); break;
        case 1: _t->btn_add_clicked(); break;
        case 2: _t->btn_del_clicked(); break;
        case 3: _t->btn_upd_clicked(); break;
        case 4: _t->btn_qry_clicked(); break;
        case 5: _t->info_record_clicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject ui_setting_floor_page::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ui_setting_floor_page.data,
      qt_meta_data_ui_setting_floor_page,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ui_setting_floor_page::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui_setting_floor_page::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui_setting_floor_page.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ui_setting_floor_page::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
