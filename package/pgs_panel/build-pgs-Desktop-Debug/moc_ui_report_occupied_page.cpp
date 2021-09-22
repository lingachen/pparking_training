/****************************************************************************
** Meta object code from reading C++ file 'ui_report_occupied_page.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ui_report_occupied_page.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ui_report_occupied_page.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui_report_occupied_page_t {
    QByteArrayData data[7];
    char stringdata0[91];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui_report_occupied_page_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui_report_occupied_page_t qt_meta_stringdata_ui_report_occupied_page = {
    {
QT_MOC_LITERAL(0, 0, 23), // "ui_report_occupied_page"
QT_MOC_LITERAL(1, 24, 18), // "btn_search_clicked"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 18), // "btn_export_clicked"
QT_MOC_LITERAL(4, 63, 19), // "info_record_clicked"
QT_MOC_LITERAL(5, 83, 3), // "row"
QT_MOC_LITERAL(6, 87, 3) // "col"

    },
    "ui_report_occupied_page\0btn_search_clicked\0"
    "\0btn_export_clicked\0info_record_clicked\0"
    "row\0col"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui_report_occupied_page[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x0a /* Public */,
       3,    0,   30,    2, 0x0a /* Public */,
       4,    2,   31,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    5,    6,

       0        // eod
};

void ui_report_occupied_page::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ui_report_occupied_page *_t = static_cast<ui_report_occupied_page *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->btn_search_clicked(); break;
        case 1: _t->btn_export_clicked(); break;
        case 2: _t->info_record_clicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject ui_report_occupied_page::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ui_report_occupied_page.data,
      qt_meta_data_ui_report_occupied_page,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ui_report_occupied_page::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui_report_occupied_page::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui_report_occupied_page.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ui_report_occupied_page::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
