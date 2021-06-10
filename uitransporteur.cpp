#include "uitransporteur.h"
#include "ui_uitransporteur.h"

UITransporteur::UITransporteur(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UITransporteur)
{
    ui->setupUi(this);
}

UITransporteur::~UITransporteur()
{
    delete ui;
}

void UITransporteur::on_validerButton_clicked()
{
    FormsValidator::clear();
    FormsValidator::registerWidget(ui->nomLineEdit,FormsValidator::LIBELLE_50);
    //FormsValidator::registerWidget(ui->codeLineEdit,FormsValidator::CODE_5);
    //FormsValidator::registerWidget(ui->telephoneLineEdit,FormsValidator::PHONE);
    if(FormsValidator::validate()){
        Model::Transporteur u;
        u.setNom(ui->nomLineEdit->text().trimmed().toUpper());
        u.setCode(ui->codeLineEdit->text().trimmed().toUpper());
        u.setTelephone(ui->telephoneLineEdit->text().trimmed());
        u.setType(ui->typeTranspComboBox->currentText() == "PARTICULIER" ? "P" : "F");
        u.setTva(ui->tVACheckBox->isChecked());
        u.setBic(ui->bICCheckBox->isChecked());
        u.setRetInt(ui->rETINTCheckBox->isChecked());
        u.setRetNat(ui->rETNATCheckBox->isChecked());

        if(mode == "Modifier"){
            u.setIdTransp(transporteur.getId());
            emit update(u);
        }else{
            emit create(u);
        }
    }else{
        FormsValidator::showErrors();
    }
}

void UITransporteur::on_annulerButton_clicked()
{
    ui->codeLineEdit->clear();
    ui->telephoneLineEdit->clear();
    ui->nomLineEdit->clear();
}

void UITransporteur::setMode(const QString &value)
{
    mode = value;
    ui->validerButton->setText(mode);
}

void UITransporteur::setTransporteur(const Model::Transporteur &value)
{
    transporteur = value;
    ui->nomLineEdit->setText(transporteur.getNom());
    ui->codeLineEdit->setText(transporteur.getCode());
    ui->telephoneLineEdit->setText(transporteur.getTelephone());
    ui->typeTranspComboBox->setCurrentText(transporteur.getType());
    ui->tVACheckBox->setChecked(transporteur.getTva());
    ui->bICCheckBox->setChecked(transporteur.getBic());
    ui->rETINTCheckBox->setChecked(transporteur.getRetInt());
    ui->rETNATCheckBox->setChecked(transporteur.getRetNat());
}
