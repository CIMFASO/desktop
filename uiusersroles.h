#ifndef USERSROLES_H
#define USERSROLES_H

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
#include "models/userroles.h"
#include "utils/checkaccessutil.h"
#include "utils/tableviewdata.h"
#include "utils/waitingspinnerwidget.h"

namespace Ui {
class UsersRoles;
}
namespace UI {
    class UsersRoles : public QDialog, public HandleData<Model::UserRoles>
    {
        Q_OBJECT

    public:
        explicit UsersRoles(QWidget *parent = nullptr);
        ~UsersRoles();
    public:
        void addItemsToTreeViewModel(const int &id);
    private slots:
        void httpResponse(QMap<QString, QByteArray> response) override;
        void tableItemActivatedSlot(const QModelIndex &index);
        void itemChanged(QStandardItem *item);

    private:
        Ui::UsersRoles *ui;
        QTableView *tableView;
        QTreeView *treeView;
        QStandardItemModel *model,*listModel;
        QList<Model::Role> roles;
        QList<Model::UserRoles> userRoles;
        int currentUserId = 0;
        WaitingSpinnerWidget *spinner;
    };
}


#endif // USERSROLES_H
