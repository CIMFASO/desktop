#ifndef TABLEVIEWDATA_H
#define TABLEVIEWDATA_H

#include <QStringList>
#include <QTableView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QHeaderView>
#include "customdelegate.h"
#include <QDebug>

class TableViewData : public QObject
{
    Q_OBJECT
    using QObject::QObject;
public:
    TableViewData();
public:
    static TableViewData& instance(){
        static TableViewData _tv;
        return _tv;
    }

    static void setData(const QList<QStringList> items,
                        QList<int> itemsToHide,
                        QStringList &headers,
                        QTableView *table,
                        QStandardItemModel *model,
                        bool displayActions = false,
                        bool customBrushEnabled = false,
                        QList<int> customBrushColumns = {},
                        QHeaderView::ResizeMode resizeMode = QHeaderView::Interactive,
                        QList<int> actionsColumns = {}
   , QMap<int, Qt::AlignmentFlag> cellsAlign = QMap<int,Qt::AlignmentFlag>());

public slots:
    static void slotModelUpdated(){
        emit instance().modelUpdated();
    }

signals:
    void modelUpdated();

private:
    static CustomDelegate *delegate;
};

#endif // TABLEVIEWDATA_H
