/****************************************************************************
** Meta object code from reading C++ file 'CamWidget.h'
**
** Created: Mon Apr 1 17:48:03 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "CamWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CamWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CamWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      24,   11,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CamWidget[] = {
    "CamWidget\0\0updatedImage\0setImage(cv::Mat)\0"
};

void CamWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CamWidget *_t = static_cast<CamWidget *>(_o);
        switch (_id) {
        case 0: _t->setImage((*reinterpret_cast< const cv::Mat(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CamWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CamWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CamWidget,
      qt_meta_data_CamWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CamWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CamWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CamWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CamWidget))
        return static_cast<void*>(const_cast< CamWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int CamWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
