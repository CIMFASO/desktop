#include "uitariflistview.h"
#include "ui_uitariflistview.h"

UITarifListView::UITarifListView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UITarifListView)
{
    ui->setupUi(this);
}

UITarifListView::~UITarifListView()
{
    delete ui;
}
