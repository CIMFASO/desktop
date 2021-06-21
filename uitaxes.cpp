#include "uitaxes.h"
#include "ui_uitaxes.h"
#include "utils/formsvalidator.h"

UITaxes::UITaxes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UITaxes)
{
    ui->setupUi(this);
}

UITaxes::~UITaxes()
{
    delete ui;
}

void UITaxes::setTaxe(const Model::Taxe &value)
{
    taxe = value;
    ui->libelleLineEdit->setText(taxe.getLibelle());
    ui->tauxLineEdit->setText(QString::number(taxe.getTaux()));
}

void UITaxes::setMode(const QString &value)
{
    mode = value;
    ui->validerButton->setText(mode);
    if(mode == "Modifier")
        ui->libelleLineEdit->setEnabled(false);
}

void UITaxes::on_validerButton_clicked()
{
    FormsValidator::clear();
    FormsValidator::registerWidget(ui->libelleLineEdit,FormsValidator::LIBELLE_50);
    FormsValidator::registerWidget(ui->tauxLineEdit,new QDoubleValidator(0,1,2));
    //FormsValidator::registerWidget(ui->telephoneLineEdit,FormsValidator::PHONE);
    if(FormsValidator::validate()){
        Model::Taxe u;
        u.setLibelle(ui->libelleLineEdit->text().trimmed().toUpper());
        u.setTaux(ui->tauxLineEdit->text().trimmed().toDouble());

        if(mode == "Modifier"){
            u.setIdTaxe(taxe.getIdTaxe());
            emit update(u);
        }else{
            emit create(u);
        }
    }else{
        FormsValidator::showErrors();
    }
}

void UITaxes::on_annulerButton_clicked()
{
    ui->libelleLineEdit->clear();
    ui->tauxLineEdit->clear();
}
