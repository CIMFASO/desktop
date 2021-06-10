#ifndef UITAXES_H
#define UITAXES_H

#include <QDialog>

namespace Ui {
class UITaxes;
}

class UITaxes : public QDialog
{
    Q_OBJECT

public:
    explicit UITaxes(QWidget *parent = nullptr);
    ~UITaxes();

private:
    Ui::UITaxes *ui;
};

#endif // UITAXES_H
