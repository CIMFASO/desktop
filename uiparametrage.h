#ifndef UIPARAMETRAGE_H
#define UIPARAMETRAGE_H

#include <QDialog>

namespace Ui {
class Parametrage;
}

namespace UI {
class Parametrage : public QDialog
{
    Q_OBJECT

public:
    explicit Parametrage(QWidget *parent = nullptr);
    ~Parametrage();

private slots:
    void on_tabWidget_currentChanged(int index);

private:
    Ui::Parametrage *ui;
};
}
#endif // UIPARAMETRAGE_H
