#include "uitransporteurlistview.h"
#include "ui_uitransporteurlistview.h"
#include "uitransporteur.h"

UITransporteurListView::UITransporteurListView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UITransporteurListView)
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

    connect(delegate,&CustomDelegate::delButtonClicked,this,&UITransporteurListView::slotDelete);
    connect(delegate,&CustomDelegate::updButtonClicked,this,&UITransporteurListView::slotUpdate);
    connect(crud->getHttpObject(),&HttpRequest::requestSuccess,this,&UITransporteurListView::httpResponse);
}

UITransporteurListView::~UITransporteurListView()
{
    delete ui;
}

void UITransporteurListView::httpResponse(QMap<QString, QByteArray> response)
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
        delegate->setCustomColumn(9);

        QJsonArray array = QJsonDocument::fromJson(response.first()).array();
        QStringList headers = {"ID","CODE","NOM TRANSPORTEUR","TELEPHONE","TYPE","TVA","BIC","RET N","RET I","ACTIONS"};

        QList<QStringList> data;
        for (int i = 0; i < array.size(); ++i) {
            QJsonObject obj = array.at(i).toObject();
            QStringList items;
            items << QString::number(obj["ID_TRANSPORTEUR"].toString().toInt())
                  << obj["CODE_TRANSPORTEUR"].toString()
                  << obj["NOM_TRANSPORTEUR"].toString()                  
                  << obj["CONTACT"].toString()
                  << (obj["TYPE_TRANSPORTEUR"].toString() == "P" ? "PARTICULIER" : "FLOTTE")
                  << obj["TVA"].toString()
                  << obj["BIC"].toString()
                  << obj["RET_N"].toString()
                  << obj["RET_I"].toString()
                  << "";
           data.append(items);
        }
        if(data.isEmpty()){
            if(spinner->isSpinning())
                spinner->stop();
            spinner->setDataSourceIsEmpty(true);
            spinner->start();
        }else{
            TableViewData::setData(data,{0,5,6,7,8},headers,ui->tableView,model,true,false,{},QHeaderView::Stretch);
            if(spinner->isSpinning())
                spinner->stop();
        }
    }
}

void UITransporteurListView::slotUpdate(const QModelIndex &index)
{
    UITransporteur *ui = new UITransporteur(this);
    Model::Transporteur m;
    m.setIdTransp(index.sibling(index.row(),0).data().toInt());
    m.setCode(index.sibling(index.row(),1).data().toString());
    m.setNom(index.sibling(index.row(),2).data().toString());
    m.setTelephone(index.sibling(index.row(),3).data().toString());
    m.setType(index.sibling(index.row(),4).data().toString());
    m.setTva(index.sibling(index.row(),5).data().toString().toInt());
    m.setBic(index.sibling(index.row(),6).data().toString().toInt());
    m.setRetNat(index.sibling(index.row(),7).data().toString().toInt());
    m.setRetInt(index.sibling(index.row(),8).data().toString().toInt());

    ui->setTransporteur(m);
    ui->setMode("Modifier");

    connect(ui,&UITransporteur::update,this,[=](const Model::Transporteur &g){
       crud->_update(&g);
    });
    connect(this,&UITransporteurListView::success,ui,&UITransporteur::close);

    ui->exec();
}

void UITransporteurListView::slotDelete(const QModelIndex &index)
{
    if(MessageBox::confirmDelete(this)){
        Model::Transporteur u;
        u.setIdTransp(index.sibling(index.row(),0).data().toInt());
        crud->_delete(&u);
    }
}


void UITransporteurListView::on_newButton_clicked()
{
    UITransporteur *u = new UITransporteur(this);
    connect(u,&UITransporteur::create,this,[=](const Model::Transporteur &d){
        crud->_create(&d);
    });
    connect(this,&UITransporteurListView::success,u,&UITransporteur::close);
    u->exec();
}

void UITransporteurListView::on_filtreLineEdit_textChanged(const QString &arg1)
{
    sortModel->setFilterKeyColumn(1);
    sortModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    sortModel->setFilterRegExp(arg1);
}
