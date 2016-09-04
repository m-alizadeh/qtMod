/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      23,   11,   11,   11, 0x08,
      33,   11,   11,   11, 0x08,
      49,   11,   11,   11, 0x08,
      65,   11,   11,   11, 0x08,
      82,   11,   11,   11, 0x08,
     102,   11,   11,   11, 0x08,
     119,   11,   11,   11, 0x08,
     138,   11,   11,   11, 0x08,
     153,   11,   11,   11, 0x08,
     169,   11,   11,   11, 0x08,
     179,   11,   11,   11, 0x08,
     196,   11,   11,   11, 0x08,
     208,   11,   11,   11, 0x08,
     219,   11,   11,   11, 0x08,
     235,   11,   11,   11, 0x08,
     253,   11,   11,   11, 0x08,
     267,   11,   11,   11, 0x08,
     279,   11,   11,   11, 0x08,
     296,   11,   11,   11, 0x08,
     314,   11,   11,   11, 0x08,
     334,   11,   11,   11, 0x08,
     352,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0start_fg()\0file_in()\0"
    "open_file_dlg()\0mod_type_updt()\0"
    "mod_order_updt()\0mod_symorder_updt()\0"
    "mod_pulse_updt()\0mod_rolloff_updt()\0"
    "mod_sps_updt()\0dev_addr_updt()\0fc_updt()\0"
    "samp_rate_updt()\0gain_updt()\0ant_updt()\0"
    "chan_sel_updt()\0master_clk_updt()\0"
    "dev_changed()\0about_slt()\0SWinInMaximize()\0"
    "SWinModMaximize()\0SWinRadioMaximize()\0"
    "SWinOutMaximize()\0handleprocErr()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->start_fg(); break;
        case 1: _t->file_in(); break;
        case 2: _t->open_file_dlg(); break;
        case 3: _t->mod_type_updt(); break;
        case 4: _t->mod_order_updt(); break;
        case 5: _t->mod_symorder_updt(); break;
        case 6: _t->mod_pulse_updt(); break;
        case 7: _t->mod_rolloff_updt(); break;
        case 8: _t->mod_sps_updt(); break;
        case 9: _t->dev_addr_updt(); break;
        case 10: _t->fc_updt(); break;
        case 11: _t->samp_rate_updt(); break;
        case 12: _t->gain_updt(); break;
        case 13: _t->ant_updt(); break;
        case 14: _t->chan_sel_updt(); break;
        case 15: _t->master_clk_updt(); break;
        case 16: _t->dev_changed(); break;
        case 17: _t->about_slt(); break;
        case 18: _t->SWinInMaximize(); break;
        case 19: _t->SWinModMaximize(); break;
        case 20: _t->SWinRadioMaximize(); break;
        case 21: _t->SWinOutMaximize(); break;
        case 22: _t->handleprocErr(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
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
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
