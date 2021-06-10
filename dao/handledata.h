#ifndef HANDLEDATA_H
#define HANDLEDATA_H

#include <QUrl>
#include <QObject>
#include <QStandardItemModel>
#include <QSettings>
#include "utils/contextmenu.h"
#include "utils/httprequest.h"
#include "crud.h"

template <class T>
class HandleData{

public:
    HandleData(){
        crud = new CRUD<T>();
        model = new QStandardItemModel;
        contextMenu = new ContextMenu();
    };

    virtual ~HandleData(){
        delete crud;
        delete model;
        delete contextMenu;
    };

    CRUD<T> *getCrud() const
    {
        return crud;
    }

    void setCrud(CRUD<T> *value)
    {
        crud = value;
    }

public slots:
    virtual void slotDelete(const QModelIndex &){};
    virtual void slotUpdate(const QModelIndex &){};
    virtual void httpResponse(QMap<QString,QByteArray>){};

protected:
    CRUD<T> *crud;
    QStandardItemModel *model;
    ContextMenu *contextMenu;
};

#endif // HANDLEDATA_H
