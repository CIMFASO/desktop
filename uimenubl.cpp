#include "uimenubl.h"
#include "ui_uimenubl.h"
#include "uibl.h"
#include "uido.h"

UIMenuBL::UIMenuBL(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UIMenuBL)
{
    ui->setupUi(this);
    on_tabWidget_tabBarClicked(0);
}

UIMenuBL::~UIMenuBL()
{
    delete ui;
}

void UIMenuBL::on_tabWidget_tabBarClicked(int index)
{
    if(index == 0){
        if(ui->tabBlCiment->layout()->itemAt(0) != nullptr){
            ui->tabBlCiment->layout()->itemAt(0)->widget()->hide();
            delete ui->tabBlCiment->layout()->takeAt(0);
        }
        UIBL *r = new UIBL(this);
        ui->tabBlCiment->layout()->addWidget(r);
    }

    if(index == 1){
        if(ui->tablBlMatieresPremieres->layout()->itemAt(0) != nullptr){
            ui->tablBlMatieresPremieres->layout()->itemAt(0)->widget()->hide();
            delete ui->tablBlMatieresPremieres->layout()->takeAt(0);
        }
        UIDO *r = new UIDO(this);
        ui->tablBlMatieresPremieres->layout()->addWidget(r);
    }
}

