#ifndef UITRANSPORTEUR_H
#define UITRANSPORTEUR_H

#include <QDialog>
#include "models/transporteur.h"
#include "utils/formsvalidator.h"

namespace Ui {
class UITransporteur;
}

class UITransporteur : public QDialog
{
    Q_OBJECT

public:
    explicit UITransporteur(QWidget *parent = nullptr);
    ~UITransporteur();
    void setTransporteur(const Model::Transporteur &value);
    void setMode(const QString &value);

signals:
    void create(const Model::Transporteur &t);
    void update(const Model::Transporteur &t);

private slots:
    void on_validerButton_clicked();
    void on_annulerButton_clicked();

private:
    Ui::UITransporteur *ui;
    QString mode;
    Model::Transporteur transporteur;
};

#endif // UITRANSPORTEUR_H
