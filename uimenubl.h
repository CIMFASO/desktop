#ifndef UIMENUBL_H
#define UIMENUBL_H

#include <QDialog>

namespace Ui {
class UIMenuBL;
}

class UIMenuBL : public QDialog
{
    Q_OBJECT

public:
    explicit UIMenuBL(QWidget *parent = nullptr);
    ~UIMenuBL();

private slots:
    void on_tabWidget_tabBarClicked(int index);

private:
    Ui::UIMenuBL *ui;
};

#endif // UIMENUBL_H
