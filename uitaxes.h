#ifndef UITAXES_H
#define UITAXES_H

#include <QDialog>
#include "models/taxe.h"

namespace Ui {
class UITaxes;
}

class UITaxes : public QDialog
{
    Q_OBJECT

public:
    explicit UITaxes(QWidget *parent = nullptr);
    ~UITaxes();

    void setTaxe(const Model::Taxe &value);

    void setMode(const QString &value);

signals:
    void create(const Model::Taxe &t);
    void update(const Model::Taxe &t);

private slots:
    void on_validerButton_clicked();

    void on_annulerButton_clicked();

private:
    Ui::UITaxes *ui;
    Model::Taxe taxe;
    QString mode;
};

#endif // UITAXES_H
