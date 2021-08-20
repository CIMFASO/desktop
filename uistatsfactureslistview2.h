#ifndef UISTATSFACTURESLISTVIEW2_H
#define UISTATSFACTURESLISTVIEW2_H

#include <QDialog>
#include "utils/messagebox.h"
#include "dao/handledata.h"
#include "utils/customdelegate.h"
#include "utils/tableviewdata.h"
#include "utils/waitingspinnerwidget.h"
#include "models/void.h"
#include <QSortFilterProxyModel>

namespace Ui {
class UIStatsFacturesListView2;
}

class UIStatsFacturesListView2 : public QDialog,public HandleData<Model::Void>
{
    Q_OBJECT

public:
    explicit UIStatsFacturesListView2(QWidget *parent = nullptr);
    ~UIStatsFacturesListView2();

private slots:
    void on_okPushButton_clicked();
    void httpResponse(QMap<QString, QByteArray> response) override;
    void slotDelete(const QModelIndex &index) override;
    void slotDetails(const QModelIndex &index);
    void on_rechercherLineEdit_textChanged(const QString &arg1);
    void on_tableView_clicked(const QModelIndex &index);
    void on_attenteRadioButton_clicked();
    void on_valideRadioButton_clicked();
    void on_controleRadioButton_clicked();
    void on_toutesRadioButton_clicked();

private:
    Ui::UIStatsFacturesListView2 *ui;
    WaitingSpinnerWidget *spinner,*spinner2;
    QStandardItemModel *detailsModel;
    CustomDelegate *delegate;
    QString du,au;
    QSortFilterProxyModel *sortModel;
};

#endif // UISTATSFACTURESLISTVIEW_H
