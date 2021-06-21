#include "uitaxeslistview.h"
#include "ui_uitaxeslistview.h"
#include "uitaxes.h"

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

    crud->setAddUrl("add_taxe.php");
    crud->setDelUrl("del_taxe.php");
    crud->setUpdUrl("upd_taxe.php");
    crud->setSelUrl("sel_taxe.php");

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
    if(response.firstKey().contains(crud->getAddUrl())
            || response.firstKey().contains(crud->getDelUrl())
            || response.firstKey().contains(crud->getUpdUrl()))
    {
        QJsonObject object = QJsonDocument::fromJson(response.first()).object();
        QString result = object["Response"].toString();
        if(result == "Ok"){
            emit success();
            crud->_select();
        }else{
            MessageBox::error(this);
        }
    }

    if(response.firstKey().contains(crud->getSelUrl())){
        model->clear();
        delegate->setCustomColumn(3);

        QJsonArray array = QJsonDocument::fromJson(response.first()).array();
        QStringList headers = {"ID","LIBELLE","TAUX","ACTIONS"};

        QList<QStringList> data;
        for (int i = 0; i < array.size(); ++i) {
            QJsonObject obj = array.at(i).toObject();
            QStringList items;
            items << QString::number(obj["ID_TAXE"].toString().toInt())
                  << obj["LIBELLE"].toString()
                  << obj["TAUX"].toString()
                  << "";
           data.append(items);
        }
        if(data.isEmpty()){
            if(spinner->isSpinning())
                spinner->stop();
            spinner->setDataSourceIsEmpty(true);
            spinner->start();
        }else{
            TableViewData::setData(data,{0},headers,ui->tableView,model,true,false,{},QHeaderView::Stretch);
            if(spinner->isSpinning())
                spinner->stop();
        }
    }
}

void UITaxesListView::slotUpdate(const QModelIndex &index)
{
    UITaxes *ui = new UITaxes(this);
    Model::Taxe m;
    m.setIdTaxe(index.sibling(index.row(),0).data().toInt());
    m.setLibelle(index.sibling(index.row(),1).data().toString());
    m.setTaux(index.sibling(index.row(),2).data().toDouble());

    ui->setTaxe(m);
    ui->setMode("Modifier");

    connect(ui,&UITaxes::update,this,[=](const Model::Taxe &g){
       crud->_update(&g);
    });
    connect(this,&UITaxesListView::success,ui,&UITaxes::close);

    ui->exec();
}

void UITaxesListView::slotDelete(const QModelIndex &index)
{
    if(MessageBox::confirmDelete(this)){
        Model::Taxe u;
        u.setIdTaxe(index.sibling(index.row(),0).data().toInt());
        crud->_delete(&u);
    }
}


void UITaxesListView::on_newButton_clicked()
{
    UITaxes *u = new UITaxes(this);
    connect(u,&UITaxes::create,this,[=](const Model::Taxe &d){
        crud->_create(&d);
    });
    connect(this,&UITaxesListView::success,u,&UITaxes::close);
    u->exec();
}

void UITaxesListView::on_searchLineEdit_textChanged(const QString &arg1)
{
    sortModel->setFilterKeyColumn(1);
    sortModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    sortModel->setFilterRegularExpression(arg1);
}
