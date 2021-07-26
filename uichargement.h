#ifndef UICHARGEMENT_H
#define UICHARGEMENT_H

#include <QDialog>
#include "models/chargement.h"
#include "dao/handledata.h"
#include "utils/formsvalidator.h"
#include <QKeyEvent>

namespace Ui {
class UIChargement;
}

class UIChargement : public QDialog,public HandleData<Model::Chargement>
{
    Q_OBJECT

public:
    explicit UIChargement(QWidget *parent = nullptr);
    ~UIChargement();

    const Model::Chargement &getChargement() const;
    void setChargement(const Model::Chargement &newChargement);

    const QString &getMode() const;
    void setMode(const QString &newMode);

signals:
    void create(const Model::Chargement &d);
    void update(const Model::Chargement &d);

private slots:
    void on_validerButton_clicked();
    void on_annulerButton_clicked();
    void httpResponse(QMap<QString, QByteArray> response) override;
    void keyPressEvent(QKeyEvent *) override;
    void on_nAutorisationLineEdit_textChanged(const QString &arg1);

private:
    Ui::UIChargement *ui;
    QString mode;
    Model::Chargement chargement;
    int idAutorisation;
};

#endif // UICHARGEMENT_H
