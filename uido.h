#ifndef UIDO_H
#define UIDO_H

#include <QDialog>
#include <QCompleter>
#include <QKeyEvent>
#include "utils/messagebox.h"
#include "dao/handledata.h"
#include "models/bl.h"
#include "models/transporteur.h"
#include "utils/customdelegate.h"
#include "utils/tableviewdata.h"
#include "models/customlistmodel.h"
#include "utils/waitingspinnerwidget.h"
#include "utils/lineeditdelegate.h"
#include <QSortFilterProxyModel>

namespace Ui {
class UIDO;
}

class UIDO : public QDialog,public HandleData<Model::BL>
{
    Q_OBJECT

public:
    explicit UIDO(QWidget *parent = nullptr);
    ~UIDO();

public:
    void afficherTotaux();
    void calculerMontant();

public slots:
    void keyPressEvent(QKeyEvent *e) override;

private slots:
    void httpResponse(QMap<QString, QByteArray> response) override;
    void slotUpdate(const QModelIndex &) override;
    void slotDelete(const QModelIndex &) override;
    void on_soumettreButton_clicked();
    void on_searchLineEdit_textChanged(const QString &arg1);
    void on_transporteurComboBox_currentIndexChanged(int index);
    void slotCheckBL(const QModelIndex &index);
    void on_tableView_clicked(const QModelIndex &index);
    void slotMontantChanged(const QModelIndex &index, QString value);
    void on_numFactureClientLineEdit_textChanged(const QString &arg1);
    void on_nomTransporteurLineEdit_textChanged(const QString &arg1);
    void on_codeTransporteurLineEdit_textChanged(const QString &arg1);

signals:
    void success();
private:
    Ui::UIDO *ui;
    WaitingSpinnerWidget *spinner;
    CustomDelegate *delegate;
    LineEditDelegate  *lineEditDelegate;
    QString numBL;
    QModelIndex selectedIndex;
    QCompleter *completer;
    QModelIndex completerIndex;
    QVariant tarif,qtite;
    CustomListModel<Model::Transporteur> *modelTransporteur;
    QSortFilterProxyModel *sortModel;
    Model::Transporteur currentTransporteur;
    double montantBrut{0},retenue{0},netAPayer{0},tva{0},bic{0},reteInt{0},quantiteTotal{0};
};

#endif // UIDO_H
