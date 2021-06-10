#ifndef SIGNIN_H
#define SIGNIN_H

#include <QDialog>
#include <QMessageBox>
#include "utils/httprequest.h"
#include "dao/handledata.h"
#include "dao/crud.h"
#include "models/user.h"

namespace Ui {
class Login;
}

class Login : public QDialog, HandleData<Model::User>
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

    void selectUserAccessRules();
private slots:
    void httpResponse(QMap<QString, QByteArray> response) override;
    void httpErrors(QString error);
    void on_pushButton_clicked(bool checked);
    void on_loginButton_clicked();
    void on_passwordEdit_textChanged(const QString &arg1);
    void on_pseudoEdit_textChanged(const QString &arg1);
    void on_mdpForgetButton_clicked();
    void on_ipButton_clicked();

signals:
    void rulesLoaded();
private:
    Ui::Login *ui;
    Model::User *user;
    bool paramsLoaded = false;
    QString loginErrorText;
};

#endif // SIGNIN_H
