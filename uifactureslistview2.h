#ifndef FACTURESLISTVIEW2_H
#define FACTURESLISTVIEW2_H

#include <QDialog>
#include "utils/messagebox.h"
#include "dao/handledata.h"
#include "utils/customdelegate.h"
#include "utils/tableviewdata.h"
#include "utils/waitingspinnerwidget.h"
#include "models/void.h"
#include <QSortFilterProxyModel>

namespace Ui {
class UIFacturesListView2;
}

class UIFacturesListView2 : public QDialog,public HandleData<Model::Void>
{
    Q_OBJECT

public:
    explicit UIFacturesListView2(QWidget *parent = nullptr);
    ~UIFacturesListView2();

    int getStatutBL();
private slots:
    void on_facturesLineEdit_textChanged(const QString &arg1);
    void httpResponse(QMap<QString, QByteArray> response) override;
    void slotValider(const QModelIndex &index);
    void slotRejeter(const QModelIndex &index);
    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::UIFacturesListView2 *ui;
    WaitingSpinnerWidget *spinner,*spinner2;
    QStandardItemModel *detailsModel;
    CustomDelegate *delegate;
    QSortFilterProxyModel *sortModel;
};

#endif // FACTURESLISTVIEW_H
