#include "uistatsfactureslistview2.h"
#include "ui_uistatsfactureslistview2.h"
#include "utils/prixformat.h"
#include "utils/checkaccessutil.h"

UIStatsFacturesListView2::UIStatsFacturesListView2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UIStatsFacturesListView2)
{
    ui->setupUi(this);
    spinner = new WaitingSpinnerWidget(ui->tableView);
    spinner2 = new WaitingSpinnerWidget(ui->detailsTableView);
    delegate = new CustomDelegate(ui->tableView,{2,3,4,5,6});
    sortModel = new QSortFilterProxyModel(this);
    detailsModel = new QStandardItemModel(this);

    ui->tableView->setItemDelegate(delegate);
    sortModel->setSourceModel(model);
    ui->tableView->setModel(sortModel);
    ui->detailsTableView->setModel(detailsModel);

    ui->duDateEdit->setDate(QDate::currentDate());
    ui->auDateEdit->setDate(QDate::currentDate());

    on_toutesRadioButton_clicked();

    delegate->getBtn1()->setIcon(QIcon(":/images/details"));

    delegate->setUpdBtnVisible(false);
    delegate->getUpdBtn()->setVisible(false);

    Model::ModuleManager manager;
    for(Model::UserRoles r : CheckAccessUtil::getUserRoles())
    {
        delegate->setDelBtnVisible(CheckAccessUtil::isAccessAllowed(manager.getDetailModuleById(Model::ModuleManager::EtatsFacturesAnnulerFacture),r.getRole().getIdRole()));
        delegate->getDelBtn()->setVisible(CheckAccessUtil::isAccessAllowed(manager.getDetailModuleById(Model::ModuleManager::EtatsFacturesAnnulerFacture),r.getRole().getIdRole()));
    }
    connect(delegate,&CustomDelegate::btn1Clicked,this,&UIStatsFacturesListView2::slotDetails);
    connect(delegate,&CustomDelegate::delButtonClicked,this,&UIStatsFacturesListView2::slotDelete);
    connect(crud->getHttpObject(),&HttpRequest::requestSuccess,this,&UIStatsFacturesListView2::httpResponse);
}

UIStatsFacturesListView2::~UIStatsFacturesListView2()
{
    delete ui;
}

void UIStatsFacturesListView2::on_okPushButton_clicked()
{
    if(ui->attenteRadioButton->isChecked())
        on_attenteRadioButton_clicked();
    else if(ui->valideRadioButton->isChecked())
        on_valideRadioButton_clicked();
    else if(ui->controleRadioButton->isChecked())
        on_controleRadioButton_clicked();
    else if(ui->toutesRadioButton->isChecked())
        on_toutesRadioButton_clicked();
}

void UIStatsFacturesListView2::httpResponse(QMap<QString, QByteArray> response)
{
    if(response.firstKey().contains(Utils::server()+"annuler_facture.php"))
    {
        QJsonObject object = QJsonDocument::fromJson(response.first()).object();
        QString result = object["Response"].toString();
        if(result == "Ok"){
            on_okPushButton_clicked();
        }else{
            MessageBox::error(this);
        }
    }

    if(response.firstKey().contains(Utils::server()+"sel_facture")){
        model->clear();
        delegate->setCustomColumn(6);
        int nb_facture =0;
        double montant = 0;

        QJsonArray array = QJsonDocument::fromJson(response.first()).array();
        QStringList headers = {"ID FACT. TRANSP.","N° FACT. CLIENT","CLIENT","MONTANT FACTURE","DATE CREATION","STATUT","ACTIONS"};

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
                  << obj["STATUT_FACT"].toString()
                  << "";

            if(obj["STATUT_FACT"].toString() == "VALIDE")
                items.append("#89ff00");
            else if(obj["STATUT_FACT"].toString() == "CONTROLE")
                items.append("#007800");
            else if(obj["STATUT_FACT"].toString() == "REJETE")
                items.append("#f00");
            else
                items.append("#fff");

           data.append(items);

           montant += obj["MONTANT_FACT"].toString().toDouble();
           nb_facture += 1;
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
            map.insert(5,Qt::AlignCenter);
            TableViewData::setData(data,{},headers,ui->tableView,model,true,true,{5},QHeaderView::Stretch,{},map);
            if(spinner->isSpinning())
                spinner->stop();
        }

        ui->nombreFactureLabel->setText("Nombre Factures : "+QString::number(nb_facture));
        ui->montantLabel->setText("Montant Total : "+PrixFormat::format(montant) + " FCFA");
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

void UIStatsFacturesListView2::slotDelete(const QModelIndex &index)
{
    if(MessageBox::question(this)){
        crud->query("annuler_facture.php?id="+QString::number(index.sibling(index.row(),0).data().toInt())+
                    +"&statut="+QString::number(0)//0 == REJETE
                    +"&iduser="+QString::number(Utils::currentUserId()));
    }
}

void UIStatsFacturesListView2::slotDetails(const QModelIndex &index)
{
    crud->query("sel_details_facture.php?id="+QString::number(index.sibling(index.row(),0).data().toInt()));
}

void UIStatsFacturesListView2::on_rechercherLineEdit_textChanged(const QString &arg1)
{
    sortModel->setFilterKeyColumn(1);
    sortModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    sortModel->setFilterRegularExpression(arg1);
}

void UIStatsFacturesListView2::on_tableView_clicked(const QModelIndex &index)
{
    slotDetails(index);
}

void UIStatsFacturesListView2::on_attenteRadioButton_clicked()
{
    du = ui->duDateEdit->date().toString("yyyy-MM-dd");
    au = ui->auDateEdit->date().toString("yyyy-MM-dd");

    crud->query("sel_facture_by_statut.php?statut=ATTENTE&du="+du+"&au="+au);
    spinner->start();
}

void UIStatsFacturesListView2::on_valideRadioButton_clicked()
{
    du = ui->duDateEdit->date().toString("yyyy-MM-dd");
    au = ui->auDateEdit->date().toString("yyyy-MM-dd");

    crud->query("sel_facture_by_statut.php?statut=VALIDE&du="+du+"&au="+au);
    spinner->start();
}

void UIStatsFacturesListView2::on_controleRadioButton_clicked()
{
    du = ui->duDateEdit->date().toString("yyyy-MM-dd");
    au = ui->auDateEdit->date().toString("yyyy-MM-dd");

    crud->query("sel_facture_by_statut.php?statut=CONTROLE&du="+du+"&au="+au);
    spinner->start();
}

void UIStatsFacturesListView2::on_toutesRadioButton_clicked()
{
    du = ui->duDateEdit->date().toString("yyyy-MM-dd");
    au = ui->auDateEdit->date().toString("yyyy-MM-dd");

    crud->query("sel_facture_all.php?du="+du+"&au="+au);
    spinner->start();
}
