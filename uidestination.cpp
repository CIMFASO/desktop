#include "uidestination.h"
#include "ui_uidestination.h"

UIDestination::UIDestination(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UIDestination)
{
    ui->setupUi(this);
}

UIDestination::~UIDestination()
{
    delete ui;
}

void UIDestination::setMode(const QString &value)
{
    mode = value;
    ui->validerButton->setText(mode);
}

void UIDestination::setDestination(const Model::Destination &value)
{
    destination = value;
    ui->nomLocaliteLineEdit->setText(destination.getNom());
    ui->tarifLineEdit->setText(QString::number(destination.getTarif()));
}

void UIDestination::on_validerButton_clicked()
{
    FormsValidator::clear();
    FormsValidator::registerWidget(ui->nomLocaliteLineEdit,FormsValidator::LIBELLE_50);
    FormsValidator::registerWidget(ui->tarifLineEdit,new QDoubleValidator(0,999999999,2,ui->tarifLineEdit));
    //FormsValidator::registerWidget(ui->telephoneLineEdit,FormsValidator::PHONE);
    if(FormsValidator::validate()){
        Model::Destination u;
        u.setNom(ui->nomLocaliteLineEdit->text().trimmed().toUpper());
        u.setTarif(ui->tarifLineEdit->text().trimmed().toDouble());
        if(mode == "Modifier"){
            u.setIdDest(destination.getId());
            emit update(u);
        }else{
            emit create(u);
        }
    }else{
        FormsValidator::showErrors();
    }
}
