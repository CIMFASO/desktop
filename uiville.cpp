#include "uiville.h"
#include "ui_uiville.h"

UIVille::UIVille(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UIVille)
{
    ui->setupUi(this);
}

UIVille::~UIVille()
{
    delete ui;
}

void UIVille::on_validerButton_clicked()
{
    FormsValidator::clear();
    FormsValidator::registerWidget(ui->nomVilleLineEdit,FormsValidator::LIBELLE_50);
    if(FormsValidator::validate()){
        Model::Ville u;
        u.setNom(ui->nomVilleLineEdit->text().trimmed().toUpper());
        if(mode == "Modifier"){
            u.setId(ville.getId());
            emit update(u);
        }else{
            emit create(u);
        }
    }else{
        FormsValidator::showErrors();
    }
}


void UIVille::on_annulerButton_clicked()
{
    close();
}

const QString &UIVille::getMode() const
{
    return mode;
}

void UIVille::setMode(const QString &newMode)
{
    mode = newMode;
    ui->validerButton->setText(mode);
}

const Model::Ville &UIVille::getVille() const
{
    return ville;
}

void UIVille::setVille(const Model::Ville &newVille)
{
    ville = newVille;
    ui->nomVilleLineEdit->setText(ville.getNom());
}

