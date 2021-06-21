#ifndef UIUSERSRIGHTS_H
#define UIUSERSRIGHTS_H

#include <QDialog>
#include <QTableView>
#include <QTreeView>
#include <QSplitter>
#include <QDebug>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QStringListModel>
#include "dao/handledata.h"
#include "models/user.h"
#include "models/accessrule.h"
#include "models/modulemanager.h"
#include "utils/waitingspinnerwidget.h"

namespace Ui {
class UsersRights;
}
namespace UI {
    class UsersRights : public QDialog, public HandleData<Model::AccessRule>
    {
        Q_OBJECT

    public:
        explicit UsersRights(QWidget *parent = nullptr);
        ~UsersRights();
    public:
        void addItemsToTreeViewModel(const int &id);
    private slots:
        void httpResponse(QMap<QString, QByteArray> response) override;
        void tableItemActivatedSlot(const QModelIndex &index);
        void itemChanged(QStandardItem *item);

    private:
        Ui::UsersRights *ui;
        QTableView *tableView;
        QTreeView *treeView;
        QStandardItemModel *model;
        QList<Model::AccessRule> rules;
        Model::ModuleManager *moduleManager;
        QStandardItemModel *listModel;
        int currentRoleId = 0;
        WaitingSpinnerWidget *spinner;
    };
}

#endif // UIUSERSRIGHTS_H
