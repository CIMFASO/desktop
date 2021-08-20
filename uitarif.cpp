#include "uitarif.h"
#include "ui_uitarif.h"

UITarif::UITarif(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UITarif)
{
    ui->setupUi(this);
}

UITarif::~UITarif()
{
    delete ui;
}

void UITarif::on_validerButton_clicked()
{

}


void UITarif::on_annulerButton_clicked()
{

}

