#include "uifactureslistview.h"
#include "ui_uifactureslistview.h"
#include "utils/prixformat.h"

UIFacturesListView::UIFacturesListView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UIFacturesListView)
{
    ui->setupUi(this);
    spinner = new WaitingSpinnerWidget(ui->tableView);
    spinner2 = new WaitingSpinnerWidget(ui->detailsTableView);
    delegate = new CustomDelegate(ui->tableView,{3,4,5,6});
    sortModel = new QSortFilterProxyModel(this);
    detailsModel = new QStandardItemModel(this);

    ui->tableView->setItemDelegate(delegate);
    sortModel->setSourceModel(model);
    ui->tableView->setModel(sortModel);
    ui->detailsTableView->setModel(detailsModel);

    crud->setSelUrl("sel_facture.php?statut="+QString::number(getStatutBL()));

    crud->_select();

    if(Utils::currentUserRoleCode() == "G0003")
        delegate->setBtn1Text("VALIDER");
    if(Utils::currentUserRoleCode() == "G0004")
        delegate->setBtn1Text("VALIDER DAL");
    if(Utils::currentUserRoleCode() == "G0005")
        delegate->setBtn1Text("VALIDER  RESP. DAL");
    if(Utils::currentUserRoleCode() == "G0006")
        delegate->setBtn1Text("CONTROLLER");
    if(Utils::currentUserRoleCode() == "G0007")
        delegate->setBtn1Text("VALIDER COMPTA");

    delegate->getBtn1()->setStyleSheet("background-color: green;color:white");
    delegate->setBtn2Text("REJETER");
    delegate->getBtn2()->setStyleSheet("background-color: red;color:white");

    delegate->setUpdBtnVisible(false);
    delegate->setDelBtnVisible(false);
    delegate->getUpdBtn()->setVisible(false);
    delegate->getDelBtn()->setVisible(false);

    connect(delegate,&CustomDelegate::btn1Clicked,this,&UIFacturesListView::slotValider);
    connect(delegate,&CustomDelegate::btn2Clicked,this,&UIFacturesListView::slotRejeter);
    connect(crud->getHttpObject(),&HttpRequest::requestSuccess,this,&UIFacturesListView::httpResponse);
}

UIFacturesListView::~UIFacturesListView()
{
    delete ui;
}

int UIFacturesListView::getStatutBL()
{
    if(Utils::currentUserRoleCode() == "G0002"){
        return 0;
    }else if(Utils::currentUserRoleCode() == "G0003"){
        return 1;
    }else if(Utils::currentUserRoleCode() == "G0004"){
        return 2;
    }else if(Utils::currentUserRoleCode() == "G0005"){
        return 3;
    }else if(Utils::currentUserRoleCode() == "G0006"){
        return 4;
    }else if(Utils::currentUserRoleCode() == "G0007"){
        return 5;
    }else
        return -1;//error
}

void UIFacturesListView::on_facturesLineEdit_textChanged(const QString &arg1)
{
    sortModel->setFilterKeyColumn(0);
    sortModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    sortModel->setFilterRegularExpression(arg1);
}

void UIFacturesListView::httpResponse(QMap<QString, QByteArray> response)
{
    if(response.firstKey().contains(Utils::server()+"annuler_facture.php")
            || response.firstKey().contains(Utils::server()+"valider_facture.php"))
    {
        QJsonObject object = QJsonDocument::fromJson(response.first()).object();
        QString result = object["Response"].toString();
        if(result == "Ok"){
            crud->_select();
        }else{
            MessageBox::error(this);
        }
    }

    if(response.firstKey().contains(crud->getSelUrl())){
        model->clear();
        delegate->setCustomColumn(5);

        QJsonArray array = QJsonDocument::fromJson(response.first()).array();
        QStringList headers = {"ID FACT. TRANSP.","N° FACT. CLIENT","CLIENT","MONTANT FACTURE","DATE CREATION","ACTIONS"};

        QList<QStringList> data;
        for (int i = 0; i < array.size(); ++i) {
            QJsonObject obj = array.at(i).toObject();
            QStringList items;

            qDebug() << obj["ID_FACT_TRANSP"].toInt();

            items << QString::number(obj["ID_FACT_TRANSP"].toString().toInt())
                  << obj["NUM_FACT_CLIENT"].toString()
                  << obj["NOM_TRANSPORTEUR"].toString()
                  << PrixFormat::format(obj["MONTANT_FACT"].toString().toDouble())
                  << Utils::dateTimeFormat(obj["DATE_CREA_FACT"].toString())
                  << "";
           data.append(items);
        }
        if(data.isEmpty()){
            if(spinner->isSpinning())
                spinner->stop();
            spinner->setDataSourceIsEmpty(true);
            spinner->start();
        }else{
            QMap<int,Qt::AlignmentFlag> map;
            map.insert(3,Qt::AlignRight);
            map.insert(4,Qt::AlignCenter);
            TableViewData::setData(data,{},headers,ui->tableView,model,true,false,{},QHeaderView::Stretch,{},map);
            if(spinner->isSpinning())
                spinner->stop();
        }
    }

    if(response.firstKey().contains(Utils::server()+"sel_details_facture.php")){
        detailsModel->clear();

        QJsonArray array = QJsonDocument::fromJson(response.first()).array();
        QStringList headers = {"N° BL","DATE BL","PRODUIT","QUANTITE","DESTINATION","MONTANT BL"};

        QList<QStringList> data;
        for (int i = 0; i < array.size(); ++i) {
            QJsonObject obj = array.at(i).toObject();
            QStringList items;

            items << QString::number(obj["NUM_BL"].toString().toInt())
                  << Utils::dateFormat(obj["DATE_BL"].toString())
                  << obj["PRODUIT"].toString()
                  << obj["QUANTITE"].toString()
                  << obj["NOM_LOCALITE"].toString()
                  << QString::number(obj["TARIF"].toString().toDouble());
           data.append(items);
        }
        if(data.isEmpty()){
            if(spinner2->isSpinning())
                spinner2->stop();
            spinner2->setDataSourceIsEmpty(true);
            spinner2->start();
        }else{
            TableViewData::setData(data,{},headers,ui->detailsTableView,detailsModel,false,false,{},QHeaderView::Stretch);
            if(spinner2->isSpinning())
                spinner2->stop();
        }
    }
}

void UIFacturesListView::slotValider(const QModelIndex &index)
{
    QString s;
    if(Utils::currentUserRoleCode() == "G0003")
        s = "VALIDE";
    else if(Utils::currentUserRoleCode() == "G0004")
        s = "DAL";
    else if(Utils::currentUserRoleCode() == "G0005")
        s = "RDAL";
    else if(Utils::currentUserRoleCode() == "G0006")
        s = "CONTROLE";
    else if(Utils::currentUserRoleCode() == "G0007")
        s = "COMPTA";

    if(MessageBox::question(this)){
        crud->query("valider_facture.php?id="+QString::number(index.sibling(index.row(),0).data().toInt())+
                    +"&s="+s
                    +"&statut="+QString::number(getStatutBL()+1)
                    +"&iduser="+QString::number(Utils::currentUserId()));
    }
}

void UIFacturesListView::slotRejeter(const QModelIndex &index)
{
    if(MessageBox::question(this)){
        crud->query("annuler_facture.php?id="+QString::number(index.sibling(index.row(),0).data().toInt())+
                    +"&statut="+QString::number(0)//0 == REJETE
                    +"&iduser="+QString::number(Utils::currentUserId()));
    }
}

void UIFacturesListView::on_tableView_clicked(const QModelIndex &index)
{
    crud->query("sel_details_facture.php?id="+QString::number(index.sibling(index.row(),0).data().toInt()));
}
