/****************************************************************************
** Meta object code from reading C++ file 'OptionsWindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../OptionsWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'OptionsWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_OptionsWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x0a,
      24,   14,   14,   14, 0x0a,
      33,   14,   14,   14, 0x0a,
      41,   14,   14,   14, 0x0a,
      53,   14,   14,   14, 0x0a,
      67,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_OptionsWindow[] = {
    "OptionsWindow\0\0accept()\0reject()\0"
    "apply()\0SourceDir()\0SourceParse()\0"
    "SourceClean()\0"
};

void OptionsWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        OptionsWindow *_t = static_cast<OptionsWindow *>(_o);
        switch (_id) {
        case 0: _t->accept(); break;
        case 1: _t->reject(); break;
        case 2: _t->apply(); break;
        case 3: _t->SourceDir(); break;
        case 4: _t->SourceParse(); break;
        case 5: _t->SourceClean(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData OptionsWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject OptionsWindow::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_OptionsWindow,
      qt_meta_data_OptionsWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &OptionsWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *OptionsWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *OptionsWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_OptionsWindow))
        return static_cast<void*>(const_cast< OptionsWindow*>(this));
    return QDialog::qt_metacast(_clname);
}

int OptionsWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
