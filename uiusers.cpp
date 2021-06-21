#include "uiusers.h"
#include "ui_uiusers.h"
#include "utils.h"

UIUsers::UIUsers(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UIUsers)
{
    ui->setupUi(this);
    ui->errorLabel->setVisible(false);
}

UIUsers::~UIUsers()
{
    delete ui;
}

void UIUsers::on_validerButton_clicked()
{
    FormsValidator::clear();
    FormsValidator::registerWidget(ui->nomLineEdit,FormsValidator::LIBELLE_50);
    FormsValidator::registerWidget(ui->emailLineEdit,FormsValidator::EMAIL);
    FormsValidator::registerWidget(ui->motDePasseLineEdit,FormsValidator::LIBELLE_100);
    //FormsValidator::registerWidget(ui->telephoneLineEdit,FormsValidator::PHONE);
    if(FormsValidator::validate()){
        if(ui->motDePasseLineEdit->text().trimmed() != ui->confirmationLineEdit->text().trimmed()){
            ui->errorLabel->setVisible(true);
            return;
        }

        Model::User u;
        u.setNom(ui->nomLineEdit->text().trimmed().toUpper());
        u.setPrenom(ui->prenomsLineEdit->text().trimmed().toUpper());
        u.setEmail(ui->emailLineEdit->text().trimmed());
        u.setTelephone(ui->nTELLineEdit->text().trimmed());
        u.setLogin(ui->loginLineEdit->text().trimmed());
        u.setPassword(ui->motDePasseLineEdit->text().trimmed());
        if(mode == "Modifier"){
            u.setIdUser(user.getId());
            emit update(u);
        }else{
            emit create(u);
        }
    }else{
        FormsValidator::showErrors();
    }
}

void UIUsers::on_annulerButton_clicked()
{

}

void UIUsers::setUser(const Model::User &value)
{
    user = value;
    ui->nomLineEdit->setText(user.getNom());
    ui->prenomsLineEdit->setText(user.getPrenom());
    ui->emailLineEdit->setText(user.getEmail());
    ui->loginLineEdit->setText(user.getLogin());
    ui->nTELLineEdit->setText(user.getTelephone());
}

void UIUsers::setMode(const QString &value)
{
    mode = value;
    ui->validerButton->setText(mode);
}

void UIUsers::on_confirmationLineEdit_textChanged(const QString &arg1)
{
    if(ui->motDePasseLineEdit->text().trimmed() != arg1.trimmed()){
        ui->errorLabel->setVisible(true);
    }else{
        ui->errorLabel->setVisible(false);
    }
}
