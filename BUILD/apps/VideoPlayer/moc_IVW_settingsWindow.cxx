/****************************************************************************
** Meta object code from reading C++ file 'IVW_settingsWindow.h'
**
** Created: Tue 19. May 16:44:43 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../apps/VideoPlayer/IVW_settingsWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'IVW_settingsWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_IVW_settingsWindow[] = {

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
      20,   19,   19,   19, 0x08,
      39,   19,   19,   19, 0x08,
      57,   19,   19,   19, 0x08,
      79,   19,   19,   19, 0x08,
     103,   19,   19,   19, 0x08,
     128,   19,   19,   19, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_IVW_settingsWindow[] = {
    "IVW_settingsWindow\0\0ReadDataFromFile()\0"
    "WriteDataOnFile()\0pushButtonAdd_Click()\0"
    "pushButtonClear_Click()\0"
    "pushButtonDelete_Click()\0"
    "pushButtonClose_Click()\0"
};

void IVW_settingsWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        IVW_settingsWindow *_t = static_cast<IVW_settingsWindow *>(_o);
        switch (_id) {
        case 0: _t->ReadDataFromFile(); break;
        case 1: _t->WriteDataOnFile(); break;
        case 2: _t->pushButtonAdd_Click(); break;
        case 3: _t->pushButtonClear_Click(); break;
        case 4: _t->pushButtonDelete_Click(); break;
        case 5: _t->pushButtonClose_Click(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData IVW_settingsWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject IVW_settingsWindow::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_IVW_settingsWindow,
      qt_meta_data_IVW_settingsWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &IVW_settingsWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *IVW_settingsWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *IVW_settingsWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_IVW_settingsWindow))
        return static_cast<void*>(const_cast< IVW_settingsWindow*>(this));
    return QDialog::qt_metacast(_clname);
}

int IVW_settingsWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
