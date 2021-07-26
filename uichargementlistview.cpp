#include "uichargementlistview.h"
#include "ui_uichargementlistview.h"
#include "uichargement.h"

UIChargementListView::UIChargementListView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UIChargementListView)
{
    ui->setupUi(this);
    spinner = new WaitingSpinnerWidget(ui->tableView);
    delegate = new CustomDelegate(ui->tableView);
    sortModel = new QSortFilterProxyModel(this);

    ui->tableView->setItemDelegate(delegate);
    sortModel->setSourceModel(model);
    ui->tableView->setModel(sortModel);

    ui->duDateEdit->setDate(QDate::currentDate());
    ui->auDateEdit->setDate(QDate::currentDate());

    crud->setAddUrl("add_chargement.php");
    crud->setDelUrl("del_chargement.php");
    crud->setUpdUrl("upd_chargement.php");
    crud->setSelUrl("sel_chargement.php");

    crud->_select();

    connect(delegate,&CustomDelegate::delButtonClicked,this,&UIChargementListView::slotDelete);
    connect(delegate,&CustomDelegate::updButtonClicked,this,&UIChargementListView::slotUpdate);
    connect(crud->getHttpObject(),&HttpRequest::requestSuccess,this,&UIChargementListView::httpResponse);
}

UIChargementListView::~UIChargementListView()
{
    delete ui;
}

void UIChargementListView::httpResponse(QMap<QString, QByteArray> response)
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
        delegate->setCustomColumn(16);

        QJsonArray array = QJsonDocument::fromJson(response.first()).array();
        QStringList headers = {"ID",
                               "N° CHARGEMENT",
                               "DATE",
                               "PRODUIT",
                               "POIDS NET",
                               "N° PESEE ",
                               "TRANSPORTEUR",
                               "CONTACT",
                               "CAMION",
                               "SEMI-REMORQUE",
                               "CHAUFFEUR",
                               "CONTACT",
                               "LIEU CHARGEMENT",
                               "DESTINATION",
                               "CODE/NAVIRE",
                               "NUM AUTORISATION",
                               "ACTIONS"};

        QList<QStringList> data;
        for (int i = 0; i < array.size(); ++i) {
            QJsonObject obj = array.at(i).toObject();
            QStringList items;

            items << QString::number(obj["ID_CHARGEMENT"].toString().toInt())
                  << obj["ID_AUTORISATION"].toString()
                  << obj["ID_CHARGEMENT"].toString()
                  << obj["DATE_CHARGEMENT"].toString()
                  << obj["PRODUIT"].toString()
                  << obj["POIDS_NET_CHARGEMENT"].toString()
                  << obj["NUMERO_PESEE_DEPART"].toString()
                  << obj["NOM_TRANSPORTEUR"].toString()
                  << obj["CONTACT"].toString()
                  << obj["CAMION_TRACTEUR"].toString()
                  << obj["SEMI_REMORQUE"].toString()
                  << obj["CHAUFFEUR"].toString()
                  << obj["CONTACT_CHAUFFEUR"].toString()
                  << obj["LIEU_CHARGEMENT"].toString()
                  << obj["DESTINATION"].toString()
                  << obj["CODE_NAVIRE"].toString()
                  << "";
            data.append(items);
        }
        if(data.isEmpty()){
            if(spinner->isSpinning())
                spinner->stop();
            spinner->setDataSourceIsEmpty(true);
            spinner->start();
        }else{
            TableViewData::setData(data,{0},headers,ui->tableView,model,true);
            if(spinner->isSpinning())
                spinner->stop();
        }
    }
}

void UIChargementListView::slotUpdate(const QModelIndex &index)
{
    UIChargement *ui = new UIChargement(this);
    Model::Chargement m;
    m.setIdChargement(index.sibling(index.row(),0).data().toInt());
    m.setCodeNavire(index.sibling(index.row(),15).data().toString());
    m.setNumPeseeDepart(index.sibling(index.row(),6).data().toString());
    m.setDateChargement(index.sibling(index.row(),3).data().toString());
    m.setSemiRemorque(index.sibling(index.row(),10).data().toString());
    m.setPoidsNet(index.sibling(index.row(),5).data().toDouble());
    Model::Autorisation a;
    a.setNumAutorisation(index.sibling(index.row(),1).data().toString());
    m.setAutorisation(a);
    ui->setChargement(m);
    ui->setMode("Modifier");

    connect(ui,&UIChargement::update,this,[=](const Model::Chargement &g){
        crud->_update(&g);
    });
    connect(this,&UIChargementListView::success,ui,&UIChargement::close);

    ui->exec();
}

void UIChargementListView::slotDelete(const QModelIndex &index)
{
    if(MessageBox::confirmDelete(this)){
        Model::Chargement u;
        u.setIdChargement(index.sibling(index.row(),0).data().toInt());
        crud->_delete(&u);
    }
}


void UIChargementListView::on_newButton_clicked()
{
    UIChargement *u = new UIChargement(this);
    connect(u,&UIChargement::create,this,[=](const Model::Chargement &d){
        crud->_create(&d);
    });
    connect(this,&UIChargementListView::success,u,&UIChargement::close);
    u->exec();
}

void UIChargementListView::on_filtreLineEdit_textChanged(const QString &arg1)
{
    sortModel->setFilterKeyColumn(1);
    sortModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    sortModel->setFilterRegularExpression(arg1);
}
