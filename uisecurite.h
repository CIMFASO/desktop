#ifndef UISECURITE_H
#define UISECURITE_H

#include <QDialog>

namespace Ui {
class Securite;
}

namespace UI {
class Securite : public QDialog
{
    Q_OBJECT

public:
    explicit Securite(QWidget *parent = nullptr);
    ~Securite();

    void handleUserRights();
private slots:
    void on_tabWidget_currentChanged(int index);
private:
    Ui::Securite *ui;
};
}

#endif // UISECURITE_H
