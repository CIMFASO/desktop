#ifndef UIBL_H
#define UIBL_H

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
#include "utils/comboboxdelegate.h"
#include "utils/lineeditdelegate.h"
#include <QStringListModel>
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
    void slotTypeCamionChanged(const QString &data,const QModelIndex &index);
    void on_numFactureClientLineEdit_textChanged(const QString &arg1);

    void on_nomTransporteurLineEdit_textChanged(const QString &arg1);

    void on_codeTransporteurLineEdit_textChanged(const QString &arg1);

signals:
    void success();
private:
    Ui::UIBL *ui;
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
    ComboBoxDelegate *typeCamionDelegate;
    QStringListModel *typeCamionModel;
    double montant{0},montantBrut{0},retenue{0},netAPayer{0},tva{0},bic{0},reteInt{0},quantiteTotal{0};
};

#endif // UIBL_H
