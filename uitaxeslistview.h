#ifndef UITAXESLISTVIEW_H
#define UITAXESLISTVIEW_H

#include <QDialog>
#include "utils/messagebox.h"
#include "dao/handledata.h"
#include "models/transporteur.h"
#include "utils/customdelegate.h"
#include "utils/tableviewdata.h"
#include "utils/waitingspinnerwidget.h"
#include <QSortFilterProxyModel>
#include "models/taxe.h"

namespace Ui {
class UITaxesListView;
}

class UITaxesListView : public QDialog,public HandleData<Model::Taxe>
{
    Q_OBJECT

public:
    explicit UITaxesListView(QWidget *parent = nullptr);
    ~UITaxesListView();

public slots:
    void on_searchLineEdit_textChanged(const QString &arg1);
private slots:
    void httpResponse(QMap<QString, QByteArray> response) override;
    void slotUpdate(const QModelIndex &index) override;
    void slotDelete(const QModelIndex &index) override;
    void on_newButton_clicked();
signals:
    void success();
private:
    Ui::UITaxesListView *ui;
    WaitingSpinnerWidget *spinner;
    CustomDelegate *delegate;
    QSortFilterProxyModel *sortModel;
};

#endif // UITAXESLISTVIEW_H
