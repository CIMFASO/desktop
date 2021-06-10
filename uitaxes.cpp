#include "uitaxes.h"
#include "ui_uitaxes.h"

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
