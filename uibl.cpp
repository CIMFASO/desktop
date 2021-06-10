#include "uibl.h"
#include "ui_uibl.h"
#include "utils/formsvalidator.h"

UIBL::UIBL(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UIBL)
{
    ui->setupUi(this);
    spinner = new WaitingSpinnerWidget(ui->tableView);
    delegate = new CustomDelegate(ui->tableView);
    sortModel = new QSortFilterProxyModel(this);
    modelTransporteur = new CustomListModel<Model::Transporteur>();

    ui->tableView->setItemDelegate(delegate);
    sortModel->setSourceModel(model);
    ui->tableView->setModel(sortModel);

    crud->setAddUrl("add_bl.php");
    crud->setDelUrl("del_bl.php");
    crud->setUpdUrl("upd_bl.php");
    crud->setSelUrl("sel_bl.php");

    delegate->setDelBtnVisible(false);
    delegate->setUpdBtnVisible(false);
    delegate->getDelBtn()->setVisible(false);
    delegate->getUpdBtn()->setVisible(false);

    crud->_select();

    ui->transporteurComboBox->setModel(modelTransporteur);
    crud->query("sel_transporteur.php");

    connect(delegate,&CustomDelegate::delButtonClicked,this,&UIBL::slotDelete);
    connect(delegate,&CustomDelegate::updButtonClicked,this,&UIBL::slotUpdate);
    connect(crud->getHttpObject(),&HttpRequest::requestSuccess,this,&UIBL::httpResponse);
}

UIBL::~UIBL()
{
    delete ui;
    delete modelTransporteur;
}

void UIBL::httpResponse(QMap<QString, QByteArray> response)
{
    if(response.firstKey().contains(Utils::server()+"add_facture.php"))
    {
        QJsonObject object = QJsonDocument::fromJson(response.first()).object();
        QString result = object["Response"].toString();
        if(result == "Ok"){
            MessageBox::success(this);
            crud->_select();
        }else{
            MessageBox::error(this);
        }
    }

    if(response.firstKey()== Utils::server()+"add_check_bl.php?num="+numBL){
        QJsonObject object = QJsonDocument::fromJson(response.first()).object();
        QString result = object["Response"].toString();
        if(result == "Ok"){
            model->item(selectedIndex.row(),7)->setCheckState(Qt::Checked);
        }else{
            model->item(selectedIndex.row(),7)->setCheckState(Qt::Unchecked);
        }
    }

    if(response.firstKey()== Utils::server()+"del_check_bl.php?num="+numBL){
        QJsonObject object = QJsonDocument::fromJson(response.first()).object();
        QString result = object["Response"].toString();
        if(result == "Ok"){
            //montantHT  -= selectedIndex.sibling(selectedIndex.row(),6).data().toString().trimmed().remove(" ").toDouble();
            model->item(selectedIndex.row(),7)->setCheckState(Qt::Unchecked);
        }else{
            model->item(selectedIndex.row(),7)->setCheckState(Qt::Checked);
        }
    }

    if(response.firstKey().contains(Utils::server()+"sel_transporteur.php")){

        QJsonArray array = QJsonDocument::fromJson(response.first()).array();

        Model::Transporteur t;
        t.setIdTransp(0);
        t.setCode("");
        t.setNom("Choisissez un transporteur");
        modelTransporteur->append(t);

        for (int i = 0; i < array.size(); ++i) {
            QJsonObject obj = array.at(i).toObject();
            Model::Transporteur t;
            t.setIdTransp(obj["ID_TRANSPORTEUR"].toInt());
            t.setCode(obj["CODE_TRANSPORTEUR"].toString());
            t.setNom(obj["NOM_TRANSPORTEUR"].toString());
            modelTransporteur->append(t);
        }
    }

    if(response.firstKey().contains(crud->getSelUrl())){
        model->clear();
        delegate->setCustomColumn(8);

        QJsonArray array = QJsonDocument::fromJson(response.first()).array();
        QStringList headers = {"N° BL","DATE BL","PRODUIT","POIDS","TRANSPORTEUR","DESTINATION","MONTANT BL","STATUT","ACTIONS"};

        QList<QStringList> data;
        for (int i = 0; i < array.size(); ++i) {
            QJsonObject obj = array.at(i).toObject();
            QStringList items;
            items << obj["NUM_BL"].toString()
                  << Utils::dateFormat(obj["DATE_BL"].toString())
                  << obj["PRODUIT"].toString()
                  << QString::number(obj["POIDS"].toDouble())
                  << obj["CODE_TRANSPORTEUR"].toString()
                  << obj["NOM_LOCALITE"].toString()
                  << QString::number(obj["MONTANT"].toDouble())
                  << (obj["STATUT_BL"].toString() == "1" ? "true" : "false")// 1 = En traitement,0 = Non traités
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
            map.insert(6,Qt::AlignRight);
            map.insert(7,Qt::AlignCenter);

            TableViewData::setData(data,{8},headers,ui->tableView,model,true,false,{},QHeaderView::Stretch,{7},map);
            if(spinner->isSpinning())
                spinner->stop();
        }
    }
}

void UIBL::slotUpdate(const QModelIndex &)
{

}

void UIBL::slotDelete(const QModelIndex &)
{

}

void UIBL::on_soumettreButton_clicked()
{
    FormsValidator::clear();
    FormsValidator::registerWidget(ui->numFactureClientLineEdit,FormsValidator::LIBELLE_30);
    if(FormsValidator::validate()){
        int r = QMessageBox::question(this,"Confirmation","Etes vous sûr de vouloir continuer ?",QMessageBox::Yes|QMessageBox::No);
        if(r == QMessageBox::Yes){
            crud->query("add_facture.php?code="+modelTransporteur->at(ui->transporteurComboBox->currentIndex()).getCode()+
                        "&montant=0&iduser="+QString::number(Utils::currentUserId())+"&num="+ui->numFactureClientLineEdit->text().trimmed());
        }
    }else{
        FormsValidator::showErrors();
    }
}

void UIBL::on_searchLineEdit_textChanged(const QString &arg1)
{
    sortModel->setFilterKeyColumn(0);
    sortModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    sortModel->setFilterRegExp(arg1);
}

void UIBL::on_transporteurComboBox_currentIndexChanged(int index)
{
    if(index <= 0)
        crud->_select();
    else
        crud->query("sel_bl.php?codeTransp="+modelTransporteur->at(index).getCode());
}

void UIBL::slotCheckBL(const QModelIndex &index)
{
    selectedIndex = index;
    numBL = index.sibling(index.row(),0).data().toString();

    if(model->item(index.row(),7)->checkState() == Qt::Checked){
        crud->query("del_check_bl.php?num="+numBL);
    }else{
        crud->query("add_check_bl.php?num="+numBL);
    }
}

void UIBL::on_tableView_clicked(const QModelIndex &index)
{
    if(index.column() == 7){
        slotCheckBL(index);
    }
}

void UIBL::on_numFactureClientLineEdit_textChanged(const QString &arg1)
{

}
