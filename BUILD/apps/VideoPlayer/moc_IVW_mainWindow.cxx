/****************************************************************************
** Meta object code from reading C++ file 'IVW_mainWindow.h'
**
** Created: Tue 19. May 16:44:42 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../apps/VideoPlayer/IVW_mainWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'IVW_mainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_IVW_mainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      27,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x08,
      46,   15,   15,   15, 0x08,
      72,   15,   15,   15, 0x08,
      98,   15,   15,   15, 0x08,
     131,   15,   15,   15, 0x08,
     157,   15,   15,   15, 0x08,
     183,   15,   15,   15, 0x08,
     214,   15,   15,   15, 0x08,
     241,   15,   15,   15, 0x08,
     272,   15,   15,   15, 0x08,
     302,   15,   15,   15, 0x08,
     334,   15,   15,   15, 0x08,
     363,   15,   15,   15, 0x08,
     394,   15,   15,   15, 0x08,
     431,  426,   15,   15, 0x08,
     497,  480,   15,   15, 0x08,
     583,  565,   15,   15, 0x08,
     642,  637,   15,   15, 0x08,
     667,  637,   15,   15, 0x08,
     704,   15,   15,   15, 0x08,
     727,   15,   15,   15, 0x08,
     763,  757,   15,   15, 0x08,
     802,   15,   15,   15, 0x08,
     847,  845,   15,   15, 0x08,
     892,   15,   15,   15, 0x08,
     917,   15,   15,   15, 0x08,
     951,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_IVW_mainWindow[] = {
    "IVW_mainWindow\0\0toolButton_CloseApp_Clicked()\0"
    "toolButton_Open_Clicked()\0"
    "toolButton_Stop_Clicked()\0"
    "toolButton_DeleteTrack_Clicked()\0"
    "toolButton_Next_Clicked()\0"
    "toolButton_Prev_Clicked()\0"
    "toolButton_PlayPause_Clicked()\0"
    "toolButton_About_Clicked()\0"
    "toolButton_UserGuide_Clicked()\0"
    "toolButton_AddFiles_Clicked()\0"
    "toolButton_RemoveList_Clicked()\0"
    "toolButton_UpTrack_Clicked()\0"
    "toolButton_DownTrack_Clicked()\0"
    "toolButton_FullScreen_Clicked()\0item\0"
    "tableWidget_itemDoubleClicked(QTableWidgetItem*)\0"
    "current,previous\0"
    "tableWidget_currentItemChanged(QTableWidgetItem*,QTableWidgetItem*)\0"
    "newState,oldState\0"
    "videoPlayer_stateChanged(Phonon::State,Phonon::State)\0"
    "time\0videoPlayer_tick(qint64)\0"
    "videoPlayer_totalTimeChanged(qint64)\0"
    "videoPlayer_finished()\0"
    "toolButton_Settings_Clicked()\0state\0"
    "on_checkBox_AllVideo_stateChanged(int)\0"
    "toolButton_SendToInteractiveWall_Clicked()\0"
    ",\0On_FinishedProcess(int,QProcess::ExitStatus)\0"
    "getInfoOfSelectedVideo()\0"
    "pushButton_InitialRange_Clicked()\0"
    "pushButton_EndRange_Clicked()\0"
};

void IVW_mainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        IVW_mainWindow *_t = static_cast<IVW_mainWindow *>(_o);
        switch (_id) {
        case 0: _t->toolButton_CloseApp_Clicked(); break;
        case 1: _t->toolButton_Open_Clicked(); break;
        case 2: _t->toolButton_Stop_Clicked(); break;
        case 3: _t->toolButton_DeleteTrack_Clicked(); break;
        case 4: _t->toolButton_Next_Clicked(); break;
        case 5: _t->toolButton_Prev_Clicked(); break;
        case 6: _t->toolButton_PlayPause_Clicked(); break;
        case 7: _t->toolButton_About_Clicked(); break;
        case 8: _t->toolButton_UserGuide_Clicked(); break;
        case 9: _t->toolButton_AddFiles_Clicked(); break;
        case 10: _t->toolButton_RemoveList_Clicked(); break;
        case 11: _t->toolButton_UpTrack_Clicked(); break;
        case 12: _t->toolButton_DownTrack_Clicked(); break;
        case 13: _t->toolButton_FullScreen_Clicked(); break;
        case 14: _t->tableWidget_itemDoubleClicked((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 15: _t->tableWidget_currentItemChanged((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QTableWidgetItem*(*)>(_a[2]))); break;
        case 16: _t->videoPlayer_stateChanged((*reinterpret_cast< Phonon::State(*)>(_a[1])),(*reinterpret_cast< Phonon::State(*)>(_a[2]))); break;
        case 17: _t->videoPlayer_tick((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 18: _t->videoPlayer_totalTimeChanged((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 19: _t->videoPlayer_finished(); break;
        case 20: _t->toolButton_Settings_Clicked(); break;
        case 21: _t->on_checkBox_AllVideo_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 22: _t->toolButton_SendToInteractiveWall_Clicked(); break;
        case 23: _t->On_FinishedProcess((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QProcess::ExitStatus(*)>(_a[2]))); break;
        case 24: _t->getInfoOfSelectedVideo(); break;
        case 25: _t->pushButton_InitialRange_Clicked(); break;
        case 26: _t->pushButton_EndRange_Clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData IVW_mainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject IVW_mainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_IVW_mainWindow,
      qt_meta_data_IVW_mainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &IVW_mainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *IVW_mainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *IVW_mainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_IVW_mainWindow))
        return static_cast<void*>(const_cast< IVW_mainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int IVW_mainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 27)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 27;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
