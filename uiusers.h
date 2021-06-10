#ifndef UIUSERS_H
#define UIUSERS_H

#include <QDialog>
#include "models/user.h"
#include "utils/formsvalidator.h"

namespace Ui {
class UIUsers;
}

class UIUsers : public QDialog
{
    Q_OBJECT

public:
    explicit UIUsers(QWidget *parent = nullptr);
    ~UIUsers();

    void setMode(const QString &value);
    void setUser(const Model::User &value);

signals:
    void create(const Model::User &user);
    void update(const Model::User &user);

private slots:
    void on_validerButton_clicked();
    void on_annulerButton_clicked();

private:
    Ui::UIUsers *ui;
    QString mode;
    Model::User user;
};

#endif // UIUSERS_H
