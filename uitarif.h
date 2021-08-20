#ifndef UITARIF_H
#define UITARIF_H

#include <QDialog>

namespace Ui {
class UITarif;
}

class UITarif : public QDialog
{
    Q_OBJECT

public:
    explicit UITarif(QWidget *parent = nullptr);
    ~UITarif();

private slots:
    void on_validerButton_clicked();

    void on_annulerButton_clicked();

private:
    Ui::UITarif *ui;
};

#endif // UITARIF_H
