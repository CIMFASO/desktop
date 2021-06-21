#ifndef FACTURESLISTVIEW_H
#define FACTURESLISTVIEW_H

#include <QDialog>
#include "utils/messagebox.h"
#include "dao/handledata.h"
#include "utils/customdelegate.h"
#include "utils/tableviewdata.h"
#include "utils/waitingspinnerwidget.h"
#include "models/void.h"
#include <QSortFilterProxyModel>

namespace Ui {
class UIFacturesListView;
}

class UIFacturesListView : public QDialog,public HandleData<Model::Void>
{
    Q_OBJECT

public:
    explicit UIFacturesListView(QWidget *parent = nullptr);
    ~UIFacturesListView();

    int getStatutBL();
private slots:
    void on_facturesLineEdit_textChanged(const QString &arg1);
    void httpResponse(QMap<QString, QByteArray> response) override;
    void slotValider(const QModelIndex &index);
    void slotRejeter(const QModelIndex &index);
    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::UIFacturesListView *ui;
    WaitingSpinnerWidget *spinner,*spinner2;
    QStandardItemModel *detailsModel;
    CustomDelegate *delegate;
    QSortFilterProxyModel *sortModel;
};

#endif // FACTURESLISTVIEW_H
