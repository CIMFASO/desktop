#include "uitaxeslistview.h"
#include "ui_uitaxeslistview.h"

UITaxesListView::UITaxesListView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UITaxesListView)
{
    ui->setupUi(this);
    spinner = new WaitingSpinnerWidget(ui->tableView);
    delegate = new CustomDelegate(ui->tableView);
    sortModel = new QSortFilterProxyModel(this);

    ui->tableView->setItemDelegate(delegate);
    sortModel->setSourceModel(model);
    ui->tableView->setModel(sortModel);

    crud->setAddUrl("add_transporteur.php");
    crud->setDelUrl("del_transporteur.php");
    crud->setUpdUrl("upd_transporteur.php");
    crud->setSelUrl("sel_transporteur.php");

    crud->_select();

    connect(delegate,&CustomDelegate::delButtonClicked,this,&UITaxesListView::slotDelete);
    connect(delegate,&CustomDelegate::updButtonClicked,this,&UITaxesListView::slotUpdate);
    connect(crud->getHttpObject(),&HttpRequest::requestSuccess,this,&UITaxesListView::httpResponse);
}

UITaxesListView::~UITaxesListView()
{
    delete ui;
}

void UITaxesListView::httpResponse(QMap<QString, QByteArray> response)
{

}

void UITaxesListView::slotUpdate(const QModelIndex &index)
{

}

void UITaxesListView::slotDelete(const QModelIndex &index)
{

}

void UITaxesListView::on_newButton_clicked()
{

}
