/****************************************************************************
** Meta object code from reading C++ file 'CodeEdit.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../CodeEdit.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CodeEdit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CodeEdit[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x0a,
      35,   25,   20,    9, 0x0a,
      53,    9,   20,    9, 0x2a,
      64,    9,   20,    9, 0x0a,
      77,   25,   20,    9, 0x0a,
      95,    9,   20,    9, 0x2a,
     106,    9,   20,    9, 0x0a,
     119,    9,    9,    9, 0x0a,
     154,  142,    9,    9, 0x08,
     195,  180,    9,    9, 0x08,
     236,  226,    9,    9, 0x08,
     268,    9,    9,    9, 0x08,
     291,    9,    9,    9, 0x08,
     317,  312,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CodeEdit[] = {
    "CodeEdit\0\0NewFile()\0bool\0pFilePath\0"
    "LoadFile(QString)\0LoadFile()\0ReloadFile()\0"
    "SaveFile(QString)\0SaveFile()\0ResaveFile()\0"
    "UpdateCursorPosition()\0pCompletion\0"
    "InsertCompletion(QString)\0pNewBlockCount\0"
    "UpdateLineNumberAreaWidth(int)\0pRect,pDy\0"
    "UpdateLineNumberArea(QRect,int)\0"
    "HighlightCurrentLine()\0HighlightSelection()\0"
    "pMod\0DocumentWasModified(bool)\0"
};

void CodeEdit::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CodeEdit *_t = static_cast<CodeEdit *>(_o);
        switch (_id) {
        case 0: _t->NewFile(); break;
        case 1: { bool _r = _t->LoadFile((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 2: { bool _r = _t->LoadFile();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: { bool _r = _t->ReloadFile();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: { bool _r = _t->SaveFile((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 5: { bool _r = _t->SaveFile();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 6: { bool _r = _t->ResaveFile();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 7: _t->UpdateCursorPosition(); break;
        case 8: _t->InsertCompletion((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->UpdateLineNumberAreaWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->UpdateLineNumberArea((*reinterpret_cast< const QRect(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 11: _t->HighlightCurrentLine(); break;
        case 12: _t->HighlightSelection(); break;
        case 13: _t->DocumentWasModified((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CodeEdit::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CodeEdit::staticMetaObject = {
    { &QPlainTextEdit::staticMetaObject, qt_meta_stringdata_CodeEdit,
      qt_meta_data_CodeEdit, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CodeEdit::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CodeEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CodeEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CodeEdit))
        return static_cast<void*>(const_cast< CodeEdit*>(this));
    return QPlainTextEdit::qt_metacast(_clname);
}

int CodeEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPlainTextEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
