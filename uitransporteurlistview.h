#ifndef UITRANSPORTEURLISTVIEW_H
#define UITRANSPORTEURLISTVIEW_H

#include <QDialog>
#include "utils/messagebox.h"
#include "dao/handledata.h"
#include "models/transporteur.h"
#include "utils/customdelegate.h"
#include "utils/tableviewdata.h"
#include "utils/waitingspinnerwidget.h"
#include <QSortFilterProxyModel>

namespace Ui {
class UITransporteurListView;
}

class UITransporteurListView : public QDialog,public HandleData<Model::Transporteur>
{
    Q_OBJECT

public:
    explicit UITransporteurListView(QWidget *parent = nullptr);
    ~UITransporteurListView();

private slots:
    void httpResponse(QMap<QString, QByteArray> response) override;
    void slotUpdate(const QModelIndex &index) override;
    void slotDelete(const QModelIndex &index) override;
    void on_newButton_clicked();

    void on_filtreLineEdit_textChanged(const QString &arg1);
signals:
    void success();

private:
    Ui::UITransporteurListView *ui;
    WaitingSpinnerWidget *spinner;
    CustomDelegate *delegate;
    QSortFilterProxyModel *sortModel;
};

#endif // UITRANSPORTEURLISTVIEW_H
