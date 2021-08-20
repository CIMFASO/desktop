#ifndef UIVILLELISTVIEW_H
#define UIVILLELISTVIEW_H

#include <QDialog>
#include "utils/messagebox.h"
#include "dao/handledata.h"
#include "models/ville.h"
#include "utils/customdelegate.h"
#include "utils/tableviewdata.h"
#include "utils/waitingspinnerwidget.h"
#include <QSortFilterProxyModel>

namespace Ui {
class UIVilleListView;
}

class UIVilleListView : public QDialog,public HandleData<Model::Ville>
{
    Q_OBJECT

public:
    explicit UIVilleListView(QWidget *parent = nullptr);
    ~UIVilleListView();

private slots:
    void httpResponse(QMap<QString, QByteArray> response) override;
    void slotUpdate(const QModelIndex &index) override;
    void slotDelete(const QModelIndex &index) override;
    void on_newButton_clicked();

    void on_nomVilleLineEdit_changed(const QString &arg1);
signals:
    void success();
private:
    Ui::UIVilleListView *ui;
    WaitingSpinnerWidget *spinner;
    CustomDelegate *delegate;
    QSortFilterProxyModel *sortModel;
};

#endif // UIVILLELISTVIEW_H
