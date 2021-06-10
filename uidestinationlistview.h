#ifndef UIDESTINATIONLISTVIEW_H
#define UIDESTINATIONLISTVIEW_H

#include <QDialog>
#include "utils/messagebox.h"
#include "dao/handledata.h"
#include "models/destination.h"
#include "utils/customdelegate.h"
#include "utils/tableviewdata.h"
#include "utils/waitingspinnerwidget.h"
#include <QSortFilterProxyModel>

namespace Ui {
class UIDestinationListView;
}

class UIDestinationListView : public QDialog,public HandleData<Model::Destination>
{
    Q_OBJECT

public:
    explicit UIDestinationListView(QWidget *parent = nullptr);
    ~UIDestinationListView();

private slots:
    void httpResponse(QMap<QString, QByteArray> response) override;
    void slotUpdate(const QModelIndex &index) override;
    void slotDelete(const QModelIndex &index) override;
    void on_newButton_clicked();

    void on_filtreLineEdit_textChanged(const QString &arg1);

signals:
    void success();
private:
    Ui::UIDestinationListView *ui;
    WaitingSpinnerWidget *spinner;
    CustomDelegate *delegate;
    QSortFilterProxyModel *sortModel;
};

#endif // UIDESTINATIONLISTVIEW_H
