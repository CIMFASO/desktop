#include "uifactureslistview.h"
#include "ui_uifactureslistview.h"

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

    crud->setSelUrl("sel_facture.php");

    crud->_select();

    delegate->setBtn1Text("VALIDER");
    delegate->getBtn1()->setStyleSheet("background-color: green;color:white");
    delegate->setBtn2Text("REJETER");
    delegate->getBtn2()->setStyleSheet("background-color: red;color:white");

    delegate->setUpdBtnVisible(false);
    delegate->setDelBtnVisible(false);
    delegate->getUpdBtn()->setVisible(false);
    delegate->getDelBtn()->setVisible(false);

    //connect(delegate,&CustomDelegate::updButtonClicked,this,&UIFacturesListView::slotUpdate);
    connect(crud->getHttpObject(),&HttpRequest::requestSuccess,this,&UIFacturesListView::httpResponse);
}

UIFacturesListView::~UIFacturesListView()
{
    delete ui;
}

void UIFacturesListView::on_facturesLineEdit_textChanged(const QString &arg1)
{
    sortModel->setFilterKeyColumn(0);
    sortModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    sortModel->setFilterRegExp(arg1);
}

void UIFacturesListView::httpResponse(QMap<QString, QByteArray> response)
{
    /*if(response.firstKey().contains(crud->getAddUrl())
            || response.firstKey().contains(crud->getDelUrl())
            || response.firstKey().contains(crud->getUpdUrl()))
    {
        QJsonObject object = QJsonDocument::fromJson(response.first()).object();
        QString result = object["Response"].toString();
        if(result == "Ok"){
            crud->_select();
        }else{
            MessageBox::error(this);
        }
    }*/


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
                  << QString::number(obj["MONTANT_FACT"].toString().toDouble())
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
            TableViewData::setData(data,{},headers,ui->tableView,model,true,false,{},QHeaderView::Stretch);
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
                  << QString::number(obj["MONTANT_BL"].toString().toDouble());
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

void UIFacturesListView::on_tableView_clicked(const QModelIndex &index)
{
    crud->query("sel_details_facture.php?id="+QString::number(index.sibling(index.row(),0).data().toInt()));
}
