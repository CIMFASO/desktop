#include "uivillelistview.h"
#include "ui_uivillelistview.h"
#include "uiville.h"

UIVilleListView::UIVilleListView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UIVilleListView)
{
    ui->setupUi(this);
    spinner = new WaitingSpinnerWidget(ui->tableView);
    delegate = new CustomDelegate(ui->tableView);
    sortModel = new QSortFilterProxyModel(this);

    ui->tableView->setItemDelegate(delegate);
    sortModel->setSourceModel(model);
    ui->tableView->setModel(sortModel);

    crud->setAddUrl("add_ville.php");
    crud->setDelUrl("del_ville.php");
    crud->setUpdUrl("upd_ville.php");
    crud->setSelUrl("sel_ville.php");

    crud->_select();

    connect(delegate,&CustomDelegate::delButtonClicked,this,&UIVilleListView::slotDelete);
    connect(delegate,&CustomDelegate::updButtonClicked,this,&UIVilleListView::slotUpdate);
    connect(crud->getHttpObject(),&HttpRequest::requestSuccess,this,&UIVilleListView::httpResponse);
}

UIVilleListView::~UIVilleListView()
{
    delete ui;
}

void UIVilleListView::httpResponse(QMap<QString, QByteArray> response)
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
        delegate->setCustomColumn(2);

        QJsonArray array = QJsonDocument::fromJson(response.first()).array();
        QStringList headers = {"ID","NOM VILLE","ACTIONS"};

        QList<QStringList> data;
        for (int i = 0; i < array.size(); ++i) {
            QJsonObject obj = array.at(i).toObject();
            QStringList items;
            items << QString::number(obj["ID_VILLE"].toString().toInt())
                  << obj["NOM_VILLE"].toString()
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

void UIVilleListView::slotUpdate(const QModelIndex &index)
{
    UIVille *ui = new UIVille(this);
    Model::Ville m;
    m.setId(index.sibling(index.row(),0).data().toInt());
    m.setNom(index.sibling(index.row(),1).data().toString());

    ui->setVille(m);
    ui->setMode("Modifier");

    connect(ui,&UIVille::update,this,[=](const Model::Ville &g){
        crud->_update(&g);
    });
    connect(this,&UIVilleListView::success,ui,&UIVille::close);

    ui->exec();
}

void UIVilleListView::slotDelete(const QModelIndex &index)
{
    if(MessageBox::confirmDelete(this)){
        Model::Ville u;
        u.setId(index.sibling(index.row(),0).data().toInt());
        crud->_delete(&u);
    }
}


void UIVilleListView::on_newButton_clicked()
{
    UIVille *u = new UIVille(this);
    connect(u,&UIVille::create,this,[=](const Model::Ville &d){
        crud->_create(&d);
    });
    connect(this,&UIVilleListView::success,u,&UIVille::close);
    u->exec();
}

void UIVilleListView::on_nomVilleLineEdit_changed(const QString &arg1)
{
    sortModel->setFilterKeyColumn(1);
    sortModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    sortModel->setFilterRegularExpression(arg1);
}
