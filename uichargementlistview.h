#ifndef UICHARGEMENTLISTVIEW_H
#define UICHARGEMENTLISTVIEW_H

#include <QDialog>
#include "utils/messagebox.h"
#include "dao/handledata.h"
#include "models/chargement.h"
#include "utils/customdelegate.h"
#include "utils/tableviewdata.h"
#include "utils/waitingspinnerwidget.h"
#include <QSortFilterProxyModel>

namespace Ui {
class UIChargementListView;
}

class UIChargementListView : public QDialog,public HandleData<Model::Chargement>
{
    Q_OBJECT

public:
    explicit UIChargementListView(QWidget *parent = nullptr);
    ~UIChargementListView();

private slots:
    void httpResponse(QMap<QString, QByteArray> response) override;
    void slotUpdate(const QModelIndex &index) override;
    void slotDelete(const QModelIndex &index) override;
    void on_filtreLineEdit_textChanged(const QString &arg1);
    void on_newButton_clicked();
signals:
    void success();
private:
    Ui::UIChargementListView *ui;
    WaitingSpinnerWidget *spinner;
    CustomDelegate *delegate;
    QSortFilterProxyModel *sortModel;
};

#endif // UICHARGEMENTLISTVIEW_H
