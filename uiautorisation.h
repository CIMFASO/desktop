#ifndef UIAUTORISATION_H
#define UIAUTORISATION_H

#include <QDialog>
#include "utils/messagebox.h"
#include "dao/handledata.h"
#include "models/autorisation.h"
#include "utils/customdelegate.h"
#include "utils/tableviewdata.h"
#include "utils/waitingspinnerwidget.h"
#include <QSortFilterProxyModel>
#include <QCompleter>
#include "models/transporteur.h"
#include "models/customlistmodel.h"


namespace Ui {
class UIAutorisation;
}

class UIAutorisation : public QDialog,public HandleData<Model::Autorisation>
{
    Q_OBJECT

public:
    explicit UIAutorisation(QWidget *parent = nullptr);
    ~UIAutorisation();

private slots:
    void httpResponse(QMap<QString, QByteArray> response) override;
    void slotUpdate(const QModelIndex &index) override;
    void slotDelete(const QModelIndex &index) override;
    void slotPrintAutorisation(const QModelIndex &index);
    void on_annulerButton_clicked();
    void on_ajouterButton_clicked();

    void on_numBELineEdit_textChanged(const QString &arg1);

private:
    Ui::UIAutorisation *ui;
    WaitingSpinnerWidget *spinner;
    CustomDelegate *delegate;
    QSortFilterProxyModel *sortModel;
    QCompleter *completer;
    QModelIndex completerIndex;
    CustomListModel<Model::Transporteur> *modelTransporteur;
};

#endif // UIAUTORISATION_H
