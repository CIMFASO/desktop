#ifndef UIBL_H
#define UIBL_H

#include <QDialog>
#include "utils/messagebox.h"
#include "dao/handledata.h"
#include "models/bl.h"
#include "models/transporteur.h"
#include "utils/customdelegate.h"
#include "utils/tableviewdata.h"
#include "models/customlistmodel.h"
#include "utils/waitingspinnerwidget.h"
#include <QSortFilterProxyModel>

namespace Ui {
class UIBL;
}

class UIBL : public QDialog,public HandleData<Model::BL>
{
    Q_OBJECT

public:
    explicit UIBL(QWidget *parent = nullptr);
    ~UIBL();

private slots:
    void httpResponse(QMap<QString, QByteArray> response) override;
    void slotUpdate(const QModelIndex &) override;
    void slotDelete(const QModelIndex &) override;
    void on_soumettreButton_clicked();
    void on_searchLineEdit_textChanged(const QString &arg1);
    void on_transporteurComboBox_currentIndexChanged(int index);
    void slotCheckBL(const QModelIndex &index);
    void on_tableView_clicked(const QModelIndex &index);

    void on_numFactureClientLineEdit_textChanged(const QString &arg1);

signals:
    void success();
private:
    Ui::UIBL *ui;
    WaitingSpinnerWidget *spinner;
    CustomDelegate *delegate;
    QString numBL;
    QModelIndex selectedIndex;
    CustomListModel<Model::Transporteur> *modelTransporteur;
    QSortFilterProxyModel *sortModel;
};

#endif // UIBL_H
