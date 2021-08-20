#include "uidestinationlistview.h"
#include "ui_uidestinationlistview.h"
#include "uidestination.h"

UIDestinationListView::UIDestinationListView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UIDestinationListView)
{
    ui->setupUi(this);
    spinner = new WaitingSpinnerWidget(ui->tableView);
    delegate = new CustomDelegate(ui->tableView);
    sortModel = new QSortFilterProxyModel(this);

    ui->tableView->setItemDelegate(delegate);
    sortModel->setSourceModel(model);
    ui->tableView->setModel(sortModel);

    crud->setAddUrl("add_destination.php");
    crud->setDelUrl("del_destination.php");
    crud->setUpdUrl("upd_destination.php");
    crud->setSelUrl("sel_destination.php");

    crud->_select();

    connect(delegate,&CustomDelegate::delButtonClicked,this,&UIDestinationListView::slotDelete);
    connect(delegate,&CustomDelegate::updButtonClicked,this,&UIDestinationListView::slotUpdate);
    connect(crud->getHttpObject(),&HttpRequest::requestSuccess,this,&UIDestinationListView::httpResponse);
}

UIDestinationListView::~UIDestinationListView()
{
    delete ui;
}

void UIDestinationListView::httpResponse(QMap<QString, QByteArray> response)
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
        delegate->setCustomColumn(4);

        QJsonArray array = QJsonDocument::fromJson(response.first()).array();
        QStringList headers = {"ID","NOM LOCALITE","TARIF","TARIF PLATEAU","ACTIONS"};

        QList<QStringList> data;
        for (int i = 0; i < array.size(); ++i) {
            QJsonObject obj = array.at(i).toObject();
            QStringList items;

            qDebug() << obj["ID_DEST"].toInt();

            items << QString::number(obj["ID_DEST"].toString().toInt())
                  << obj["NOM_LOCALITE"].toString()
                  << QString::number(obj["TARIF"].toString().toDouble())
                  << QString::number(obj["TARIF_PLAT"].toString().toDouble())
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

void UIDestinationListView::slotUpdate(const QModelIndex &index)
{
    UIDestination *ui = new UIDestination(this);
    Model::Destination m;
    m.setIdDest(index.sibling(index.row(),0).data().toInt());
    m.setNom(index.sibling(index.row(),1).data().toString());
    m.setTarif(index.sibling(index.row(),2).data().toDouble());
    m.setTarifPlat(index.sibling(index.row(),3).data().toDouble());

    ui->setDestination(m);
    ui->setMode("Modifier");

    connect(ui,&UIDestination::update,this,[=](const Model::Destination &g){
       crud->_update(&g);
    });
    connect(this,&UIDestinationListView::success,ui,&UIDestination::close);

    ui->exec();
}

void UIDestinationListView::slotDelete(const QModelIndex &index)
{
    if(MessageBox::confirmDelete(this)){
        Model::Destination u;
        u.setIdDest(index.sibling(index.row(),0).data().toInt());
        crud->_delete(&u);
    }
}


void UIDestinationListView::on_newButton_clicked()
{
    UIDestination *u = new UIDestination(this);
    connect(u,&UIDestination::create,this,[=](const Model::Destination &d){
        crud->_create(&d);
    });
    connect(this,&UIDestinationListView::success,u,&UIDestination::close);
    u->exec();
}

void UIDestinationListView::on_filtreLineEdit_textChanged(const QString &arg1)
{
    sortModel->setFilterKeyColumn(1);
    sortModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    sortModel->setFilterRegularExpression(arg1);
}
