#ifndef UIPARAMSROLES_H
#define UIPARAMSROLES_H

#include <QDialog>
#include "models/userroles.h"
#include "utils/tableviewdata.h"
#include "dao/handledata.h"
#include "utils/messagebox.h"
#include "models/customlistmodel.h"
#include "utils/waitingspinnerwidget.h"

namespace Ui {
class ParamsRoles;
}

namespace UI {
class ParamsRoles : public QDialog,public HandleData<Model::Role>
{
    Q_OBJECT

public:
    explicit ParamsRoles(QWidget *parent = nullptr);
    ~ParamsRoles();

private slots:
    void on_validerButton_clicked();

    void on_annulerButton_clicked();

    void httpResponse(QMap<QString, QByteArray> response) override;
    void slotDelete(const QModelIndex &index) override ;
    void slotUpdate(const QModelIndex &index) override ;

private:
    Ui::ParamsRoles *ui;
    QStandardItemModel *model;
    CustomDelegate *delegate;
    int idRole;
    WaitingSpinnerWidget *spinner;
};
}
#endif // UIPARAMSROLES_H
