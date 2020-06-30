/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../MainWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      34,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      26,   11,   11,   11, 0x0a,
      53,   47,   42,   11, 0x0a,
      75,   11,   42,   11, 0x2a,
     100,   94,   90,   11, 0x0a,
     127,   11,   42,   11, 0x0a,
     142,   47,   42,   11, 0x0a,
     166,   11,   42,   11, 0x2a,
     188,  183,   11,   11, 0x0a,
     211,   11,   11,   11, 0x2a,
     227,   11,   11,   11, 0x0a,
     238,  183,   11,   11, 0x0a,
     262,   11,   11,   11, 0x2a,
     290,  279,   42,   11, 0x0a,
     323,  183,   42,   11, 0x2a,
     348,   11,   11,   11, 0x0a,
     354,   11,   11,   11, 0x0a,
     361,   11,   11,   11, 0x0a,
     369,   11,   11,   11, 0x0a,
     378,   11,   11,   11, 0x0a,
     385,   11,   11,   11, 0x0a,
     392,   11,   11,   11, 0x0a,
     404,   11,   11,   11, 0x0a,
     411,   11,   11,   11, 0x0a,
     421,   11,   11,   11, 0x0a,
     445,  436,   11,   11, 0x0a,
     462,  436,   11,   11, 0x0a,
     478,  436,   11,   11, 0x0a,
     493,   11,   11,   11, 0x0a,
     500,   11,   11,   11, 0x0a,
     516,  508,   11,   11, 0x0a,
     545,   11,   11,   11, 0x08,
     561,  556,   11,   11, 0x08,
     587,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0NewDocument()\0ResetDocument()\0"
    "bool\0pPath\0OpenDocument(QString)\0"
    "OpenDocument()\0int\0pList\0"
    "OpenDocuments(QStringList)\0SaveDocument()\0"
    "SaveAsDocument(QString)\0SaveAsDocument()\0"
    "pDoc\0CloseDocument(QString)\0CloseDocument()\0"
    "CloseAll()\0CloseAllOthers(QString)\0"
    "CloseAllOthers()\0pDoc,pPath\0"
    "ReplaceDocument(QString,QString)\0"
    "ReplaceDocument(QString)\0Cut()\0Copy()\0"
    "Paste()\0Delete()\0Undo()\0Redo()\0"
    "SelectAll()\0Find()\0Options()\0"
    "ExportToHTML()\0pChecked\0LineNumber(bool)\0"
    "GuideLine(bool)\0WordWrap(bool)\0Font()\0"
    "About()\0pWindow\0SetActiveSubWindow(QWidget*)\0"
    "UpdateUi()\0pMod\0DocumentWasModified(bool)\0"
    "UpdateViewMenu()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->NewDocument(); break;
        case 1: _t->ResetDocument(); break;
        case 2: { bool _r = _t->OpenDocument((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: { bool _r = _t->OpenDocument();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: { int _r = _t->OpenDocuments((*reinterpret_cast< const QStringList(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 5: { bool _r = _t->SaveDocument();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 6: { bool _r = _t->SaveAsDocument((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 7: { bool _r = _t->SaveAsDocument();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 8: _t->CloseDocument((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->CloseDocument(); break;
        case 10: _t->CloseAll(); break;
        case 11: _t->CloseAllOthers((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 12: _t->CloseAllOthers(); break;
        case 13: { bool _r = _t->ReplaceDocument((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 14: { bool _r = _t->ReplaceDocument((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 15: _t->Cut(); break;
        case 16: _t->Copy(); break;
        case 17: _t->Paste(); break;
        case 18: _t->Delete(); break;
        case 19: _t->Undo(); break;
        case 20: _t->Redo(); break;
        case 21: _t->SelectAll(); break;
        case 22: _t->Find(); break;
        case 23: _t->Options(); break;
        case 24: _t->ExportToHTML(); break;
        case 25: _t->LineNumber((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 26: _t->GuideLine((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 27: _t->WordWrap((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 28: _t->Font(); break;
        case 29: _t->About(); break;
        case 30: _t->SetActiveSubWindow((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 31: _t->UpdateUi(); break;
        case 32: _t->DocumentWasModified((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 33: _t->UpdateViewMenu(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 34)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 34;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
