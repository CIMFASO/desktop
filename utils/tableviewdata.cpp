#include "tableviewdata.h"

CustomDelegate *TableViewData::delegate = nullptr;

 TableViewData::TableViewData() {}

 void TableViewData::setData(const QList<QStringList> items,
                             QList<int> itemsToHide,
                             QStringList &headers,
                             QTableView *table,
                             QStandardItemModel *model,
                             bool displayActions,
                             bool customBrushEnabled,
                             QList<int> customBrushColumns,
                             QHeaderView::ResizeMode resizeMode,
                             QList<int> actionsColumns,
                             QMap<int,Qt::AlignmentFlag> cellsAlign)
 {
     int size = items.count();
     int size2 = customBrushEnabled ? items.at(0).count()-1 : items.at(0).count();
     //ajoute les lignes de la tableView
     for (int i = 0; i < size; ++i) {
         QList<QStandardItem*> liste;
         for(int j=0; j < size2; j++){

             QString str = items.at(i).at(j);
             QStandardItem *item = new QStandardItem();
             item->setTextAlignment(cellsAlign.value(j,Qt::AlignVCenter));

             if(customBrushEnabled
                     && customBrushColumns.contains(j)
                     && items.at(i).last().contains("#")
                     && items.at(i).last() != "#fff")
             {
                 QColor color = QColor(items.at(i).last());
                 item->setBackground(QBrush(color));
                 item->setForeground(QBrush(Qt::white));
                 item->setTextAlignment(Qt::AlignCenter);
             }

             if(actionsColumns.contains(j)){
                 if(str == "false"){
                     item->setCheckState(Qt::Unchecked);
                 }
                 else{
                     item->setCheckState(Qt::Checked);
                 }
                 str = "";
                 item->setTextAlignment(Qt::AlignCenter);
             }

             item->setText(str);
             liste.append(item);
         }
         model->appendRow(liste);
     }

     //cache les colonnes à cacher
     for (int i = 0; i < itemsToHide.count(); ++i) {
         table->setColumnHidden(itemsToHide.at(i),true);
     }
     //Ajoute les entêtes des colonnes
     for (int i = 0; i < size2; ++i) {
         model->setHeaderData(i,Qt::Horizontal,headers.at(i));
     }
     table->setAlternatingRowColors(true);
     table->resizeColumnsToContents();
     table->horizontalHeader()->setSectionResizeMode(resizeMode);
     table->horizontalHeader()->setStretchLastSection(true);
     table->verticalHeader()->setVisible(false);
     table->verticalHeader()->setDefaultSectionSize(table->verticalHeader()->fontMetrics().height());
     table->setSortingEnabled(true);
     //slotModelUpdated();
 }
