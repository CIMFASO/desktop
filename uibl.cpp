#include "uibl.h"
#include "ui_uibl.h"
#include "utils/formsvalidator.h"
#include "utils/prixformat.h"

UIBL::UIBL(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UIBL)
{
    ui->setupUi(this);
    spinner = new WaitingSpinnerWidget(ui->tableView);
    //delegate = new CustomDelegate(ui->tableView);
    sortModel = new QSortFilterProxyModel(this);
    modelTransporteur = new CustomListModel<Model::Transporteur>();
    lineEditDelegate = new LineEditDelegate(this);

    lineEditDelegate->setValidator(new QDoubleValidator(0,9999999999,0));
    ui->tableView->setItemDelegateForColumn(7,lineEditDelegate);

    //ui->tableView->setItemDelegate(delegate);
    sortModel->setSourceModel(model);
    ui->tableView->setModel(sortModel);

    crud->setAddUrl("add_bl.php");
    crud->setDelUrl("del_bl.php");
    crud->setUpdUrl("upd_bl.php");
    crud->setSelUrl("sel_bl.php");

    crud->query("sel_taxe.php");

    /*delegate->setDelBtnVisible(false);
    delegate->setUpdBtnVisible(false);
    delegate->getDelBtn()->setVisible(false);
    delegate->getUpdBtn()->setVisible(false);*/

    completer    = new QCompleter(this);
    completer->setModel(modelTransporteur);
    completer->setMaxVisibleItems(30);
    completer->setCompletionRole(Qt::DisplayRole);
    completer->setCompletionMode(QCompleter::PopupCompletion);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->nomTransporteurLineEdit->setCompleter(completer);

    QObject::connect(completer, QOverload<const QModelIndex &>::of(&QCompleter::highlighted),[=](const QModelIndex &i){
        completerIndex = i;
        currentTransporteur = modelTransporteur->getById(completerIndex.data(Qt::UserRole).toInt());
    });

    //crud->_select();

    crud->query("sel_transporteur.php");

    QObject::connect(lineEditDelegate,&LineEditDelegate::dataChanged,this,&UIBL::slotMontantChanged);
    //connect(delegate,&CustomDelegate::delButtonClicked,this,&UIBL::slotDelete);
    //connect(delegate,&CustomDelegate::updButtonClicked,this,&UIBL::slotUpdate);
    connect(crud->getHttpObject(),&HttpRequest::requestSuccess,this,&UIBL::httpResponse);
}

UIBL::~UIBL()
{
    delete ui;
    delete modelTransporteur;
}

void UIBL::afficherTotaux()
{
    ui->totalLabel2->setText("TOTAL BRUT : <b style=color:yellow>" +PrixFormat::format(montantBrut)+ "</b> FCFA");
    ui->totalLabel1->setText("RETENUE("+QString::number(Utils::RETN()*100)+"%) : <b style=color:yellow>"+PrixFormat::format(retenue)+ "</b> FCFA");
    ui->totalLabel3->setText("TVA("+QString::number(Utils::TVA()*100)+"%) : <b style=color:yellow>"+PrixFormat::format(tva)+ "</b> FCFA");
    ui->totalLabel4->setText("BIC("+QString::number(Utils::BIC()*100)+"%) : <b style=color:yellow>"+PrixFormat::format(bic)+ "</b> FCFA");
    ui->totalLabel->setText("NET A PAYER : <b style=color:yellow>" +PrixFormat::format(netAPayer)+ "</b>  FCFA");
}

void UIBL::calculerMontant()
{
    retenue = qRound(montantBrut * Utils::RETN()* (currentTransporteur.getRetNat() ? 1 : 0));
    tva = qRound(montantBrut * Utils::TVA()* (currentTransporteur.getTva() ? 1 : 0));
    bic = qRound(montantBrut * Utils::BIC()* (currentTransporteur.getBic() ? 1 : 0));
    reteInt = qRound(montantBrut * Utils::RETI()* (currentTransporteur.getRetInt() ? 1 : 0));
    netAPayer = montantBrut - retenue + tva - bic /*- reteInt*/;
}

void UIBL::httpResponse(QMap<QString, QByteArray> response)
{
    if(response.firstKey().contains(Utils::server()+"add_facture.php")
            || response.firstKey().contains(Utils::server()+"upd_montant_bl.php"))
    {
        QJsonObject object = QJsonDocument::fromJson(response.first()).object();
        QString result = object["Response"].toString();
        if(result == "Ok"){
            MessageBox::success(this);
            on_nomTransporteurLineEdit_textChanged(ui->nomTransporteurLineEdit->text().trimmed());
        }else{
            MessageBox::error(this);
        }
    }

    if(response.firstKey().contains(Utils::server()+"sel_taxe.php")){
        QJsonArray array = QJsonDocument::fromJson(response.first()).array();
        QSettings s;
        s.beginGroup("TAXES");
        for (int i = 0; i < array.size(); ++i) {
            QJsonObject obj = array.at(i).toObject();
            if(obj["LIBELLE"].toString() == "TVA")
                s.setValue("TVA",obj["TAUX"].toString().toDouble());
            else if(obj["LIBELLE"].toString() == "BIC")
                s.setValue("BIC",obj["TAUX"].toString().toDouble());
            else if(obj["LIBELLE"].toString() == "RET N.")
                s.setValue("RET_N",obj["TAUX"].toString().toDouble());
            else if(obj["LIBELLE"].toString() == "RET I.")
                s.setValue("RET_I",obj["TAUX"].toString().toDouble());
        }
        s.endGroup();
    }

    if(response.firstKey()== Utils::server()+"add_check_bl.php?num="+numBL){
        QJsonObject object = QJsonDocument::fromJson(response.first()).object();
        QString result = object["Response"].toString();
        if(result == "Ok"){
            model->item(selectedIndex.row(),8)->setCheckState(Qt::Checked);
            montantBrut += tarif.toString().remove(" ").toDouble();
            calculerMontant();
            afficherTotaux();
        }else{
            model->item(selectedIndex.row(),8)->setCheckState(Qt::Unchecked);
        }
    }

    if(response.firstKey()== Utils::server()+"del_check_bl.php?num="+numBL){
        QJsonObject object = QJsonDocument::fromJson(response.first()).object();
        QString result = object["Response"].toString();
        if(result == "Ok"){
            //montantHT  -= selectedIndex.sibling(selectedIndex.row(),6).data().toString().trimmed().remove(" ").toDouble();
            model->item(selectedIndex.row(),8)->setCheckState(Qt::Unchecked);
            montantBrut -= tarif.toString().remove(" ").toDouble();
            calculerMontant();
            afficherTotaux();
        }else{
            model->item(selectedIndex.row(),8)->setCheckState(Qt::Checked);
        }
    }

    if(response.firstKey().contains(Utils::server()+"sel_transporteur.php")){

        QJsonArray array = QJsonDocument::fromJson(response.first()).array();

        for (int i = 0; i < array.size(); ++i) {
            QJsonObject obj = array.at(i).toObject();
            Model::Transporteur t;
            t.setIdTransp(obj["ID_TRANSPORTEUR"].toString().toInt());
            t.setCode(obj["CODE_TRANSPORTEUR"].toString());
            t.setNom(obj["NOM_TRANSPORTEUR"].toString());
            t.setTva(obj["TVA"].toString().toInt() == 1 ? true : false);
            t.setBic(obj["BIC"].toString().toInt() == 1 ? true : false);
            t.setRetInt(obj["RET_I"].toString().toInt() == 1 ? true : false);
            t.setRetNat(obj["RET_N"].toString().toInt() == 1 ? true : false);
            modelTransporteur->append(t);
        }
    }

    if(response.firstKey().contains(crud->getSelUrl())){
        model->clear();
        //delegate->setCustomColumn(8);
        montantBrut = retenue = netAPayer = tva = bic = reteInt =  0;

        if(ui->nomTransporteurLineEdit->text().trimmed().contains("PARTICULIER",Qt::CaseInsensitive)){
            ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
        }else{
            ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        }

        QJsonArray array = QJsonDocument::fromJson(response.first()).array();
        QStringList headers = {"N° BL","CODE TRANSPORTEUR","TRANSPORTEUR","DATE BL","PRODUIT","POIDS","DESTINATION","MONTANT BL","STATUT"};

        QList<QStringList> data;
        for (int i = 0; i < array.size(); ++i) {
            QJsonObject obj = array.at(i).toObject();
            QStringList items;
            items << obj["NUM_BL"].toString()
                  << obj["CODE_TRANSPORTEUR"].toString()
                  << obj["NOM_TRANSPORTEUR"].toString()
                  << Utils::dateFormat(obj["DATE_BL"].toString())
                  << obj["PRODUIT"].toString()
                  << QString::number(obj["QUANTITE"].toString().toDouble())
                  << obj["NOM_LOCALITE"].toString()
                  << PrixFormat::format(obj["MONTANT_BL"].toString().toDouble())
                  << (obj["STATUT_BL"].toString() == "1" ? "true" : "false");// 1 = En traitement,0 = Non traités;

            if(obj["STATUT_BL"].toString() == "1"){
                montantBrut += obj["MONTANT_BL"].toString().toDouble();
            }

            data.append(items);
        }

        calculerMontant();
        afficherTotaux();

        if(data.isEmpty()){
            if(spinner->isSpinning())
                spinner->stop();
            spinner->setDataSourceIsEmpty(true);
            spinner->start();
        }else{
            QMap<int,Qt::AlignmentFlag> map;
            map.insert(6,Qt::AlignRight);
            map.insert(7,Qt::AlignCenter);

            TableViewData::setData(data,{},headers,ui->tableView,model,true,false,{},QHeaderView::Stretch,{8},map);
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
    FormsValidator::registerWidget(ui->nomTransporteurLineEdit,FormsValidator::LIBELLE_50);
    FormsValidator::registerWidget(ui->numFactureClientLineEdit,FormsValidator::LIBELLE_30);
    if(FormsValidator::validate()){
        int r = QMessageBox::question(this,"Confirmation","Etes vous sûr de vouloir continuer ?",QMessageBox::Yes|QMessageBox::No);
        if(r == QMessageBox::Yes){
            crud->query("add_facture.php?code="+modelTransporteur->getByLabel(completerIndex.data().toString()).getCode()+
                        "&montant="+QString::number(netAPayer)+"&iduser="+QString::number(Utils::currentUserId())+"&num="+ui->numFactureClientLineEdit->text().trimmed());
        }
    }else{
        FormsValidator::showErrors();
    }
}

void UIBL::on_searchLineEdit_textChanged(const QString &arg1)
{
    sortModel->setFilterKeyColumn(0);
    sortModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    sortModel->setFilterRegularExpression(arg1);
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

    if(model->item(index.row(),8)->checkState() == Qt::Checked){
        crud->query("del_check_bl.php?num="+numBL);
    }else{
        crud->query("add_check_bl.php?num="+numBL);
    }
}

void UIBL::on_tableView_clicked(const QModelIndex &index)
{
    tarif = index.sibling(index.row(),7).data();

    if(index.column() == 8){
        slotCheckBL(index);
    }
}

void UIBL::slotMontantChanged(const QModelIndex &index, QString value)
{
    int r = QMessageBox::warning(this,"Attention.","Êtes-vous sûr de vouloir modifier le montant de ce bl ?",QMessageBox::Yes|QMessageBox::No);
    if(r == QMessageBox::Yes){
        QString id = index.sibling(index.row(),0).data().toString();
        crud->query("upd_montant_bl.php?num="+id+"&montant="+QString::number(value.trimmed().toDouble()));
    }
}

void UIBL::on_numFactureClientLineEdit_textChanged(const QString &arg1)
{

}

void UIBL::on_nomTransporteurLineEdit_textChanged(const QString &arg1)
{
    if(arg1.trimmed().isEmpty())
        crud->_select();
    else
        crud->query("sel_bl.php?codeTransp="+modelTransporteur->getByLabel(arg1).getCode());
}

void UIBL::on_codeTransporteurLineEdit_textChanged(const QString &arg1)
{
    //crud->query("sel_bl.php?codeTransp="+arg1);
}

void UIBL::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return){
        if(ui->codeTransporteurLineEdit->hasFocus()){
            crud->query("sel_bl.php?codeTransp="+ui->codeTransporteurLineEdit->text().trimmed());
        }
    }
}

