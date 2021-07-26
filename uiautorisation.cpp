#include "uiautorisation.h"
#include "ui_uiautorisation.h"
#include "utils/formsvalidator.h"
#include "documents.h"

UIAutorisation::UIAutorisation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UIAutorisation)
{
    ui->setupUi(this);
    spinner = new WaitingSpinnerWidget(ui->tableView);
    delegate = new CustomDelegate(ui->tableView,{2,3,4,5,6});
    sortModel = new QSortFilterProxyModel(this);
    modelTransporteur = new CustomListModel<Model::Transporteur>();

    ui->tableView->setItemDelegate(delegate);
    sortModel->setSourceModel(model);
    ui->tableView->setModel(sortModel);

    //ui->duDateEdit->setDate(QDate::currentDate());
    //ui->auDateEdit->setDate(QDate::currentDate());

    completer    = new QCompleter(this);
    completer->setModel(modelTransporteur);
    completer->setMaxVisibleItems(30);
    completer->setCompletionRole(Qt::DisplayRole);
    completer->setCompletionMode(QCompleter::PopupCompletion);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->transporteurLineEdit->setCompleter(completer);

    QObject::connect(completer, QOverload<const QModelIndex &>::of(&QCompleter::highlighted),[=](const QModelIndex &i){
        completerIndex = i;
    });

    crud->query("sel_transporteur.php");

    crud->setAddUrl("add_autorisation.php");
    crud->setDelUrl("del_autorisation.php");
    crud->setUpdUrl("upd_autorisation.php");
    crud->setSelUrl("sel_autorisation.php");

    crud->_select();
    spinner->start();

    delegate->getBtn1()->setIcon(QIcon(":/images/print"));

    connect(delegate,&CustomDelegate::delButtonClicked,this,&UIAutorisation::slotDelete);
    connect(delegate,&CustomDelegate::updButtonClicked,this,&UIAutorisation::slotUpdate);
    connect(delegate,&CustomDelegate::btn1Clicked,this,&UIAutorisation::slotPrintAutorisation);
    connect(crud->getHttpObject(),&HttpRequest::requestSuccess,this,&UIAutorisation::httpResponse);
}

UIAutorisation::~UIAutorisation()
{
    delete ui;
    delete modelTransporteur;
}

void UIAutorisation::httpResponse(QMap<QString, QByteArray> response)
{
    if(response.firstKey().contains(crud->getAddUrl())
        || response.firstKey().contains(crud->getDelUrl())
        || response.firstKey().contains(crud->getUpdUrl()))
    {
        QJsonObject object = QJsonDocument::fromJson(response.first()).object();
        QString result = object["Response"].toString();
        result == "Ok" ? MessageBox::success(this) : MessageBox::error(this);
        if(result == "Ok"){
            crud->_select();
            ui->chauffeurLineEdit->clear();
            ui->contactChauffeurLineEdit->clear();
            ui->numCamionLineEdit->clear();
            ui->numBELineEdit->clear();
            ui->transporteurLineEdit->clear();
            ui->lieuChargementLineEdit->clear();
            ui->destinationLineEdit->clear();
        }else{
            MessageBox::error(this);
        }
    }

    if(response.firstKey().contains(Utils::server()+"sel_transporteur.php")){

        QJsonArray array = QJsonDocument::fromJson(response.first()).array();
        modelTransporteur->clear();
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
        delegate->setCustomColumn(11);

        QJsonArray array = QJsonDocument::fromJson(response.first()).array();
        QStringList headers = {"N° AUTORISATION",
                               "N° BE",
                               "DATE",
                               "TRANSPORTEUR",
                               "CONTACT",
                               "PRODUIT",
                               "CHAUFFEUR",
                               "CONTACT",
                               "LIEU CHARGEMENT",
                               "DESTINATION",
                               "N° CAMION",
                               "ACTIONS"};

        QList<QStringList> data;
        for (int i = 0; i < array.size(); ++i) {
            QJsonObject obj = array.at(i).toObject();
            QStringList items;

            items << obj["ID_AUTORISATION"].toString()
                  << obj["NUMERO_BE"].toString()
                  << obj["DATE_AUTORISATION"].toString()
                  << obj["NOM_TRANSPORTEUR"].toString()
                  << obj["CONTACT"].toString()
                  << obj["PRODUIT"].toString()
                  << obj["CHAUFFEUR"].toString()
                  << obj["CONTACT_CHAUFFEUR"].toString()
                  << obj["LIEU_CHARGEMENT"].toString()
                  << obj["DESTINATION"].toString()
                  << obj["CAMION_TRACTEUR"].toString()
                  << "";
            data.append(items);
        }

        if(data.isEmpty()){
            if(spinner->isSpinning())
                spinner->stop();
            spinner->setDataSourceIsEmpty(true);
            spinner->start();
        }else{
            TableViewData::setData(data,{},headers,ui->tableView,model,true,false,{});
            if(spinner->isSpinning())
                spinner->stop();
        }
    }
}

void UIAutorisation::slotUpdate(const QModelIndex &index)
{

}

void UIAutorisation::slotDelete(const QModelIndex &index)
{

}

void UIAutorisation::slotPrintAutorisation(const QModelIndex &index)
{

    if(MessageBox::question(this,"Êtes-vous sûr de vouloir imprimer cette autorisation ?")){
        Model::Autorisation c;
        c.setNumAutorisation(index.sibling(index.row(),0).data().toString());
        c.setChauffeur(index.sibling(index.row(),6).data().toString());
        c.setCamion(index.sibling(index.row(),10).data().toString());
        c.setContactChauffeur(index.sibling(index.row(),7).data().toString());
        c.setLieuChargement(index.sibling(index.row(),8).data().toString());
        c.setDestination(index.sibling(index.row(),9).data().toString());
        c.setProduit(index.sibling(index.row(),5).data().toString());
        c.setNumeroBE(index.sibling(index.row(),1).data().toString());
        Model::Transporteur t;
        t.setNom(index.sibling(index.row(),3).data().toString());
        t.setTelephone(index.sibling(index.row(),4).data().toString());
        c.setTransporteur(t);
        // print  now ----------
        Documents d;
        d.autorisation(c);
    }
}


void UIAutorisation::on_annulerButton_clicked()
{

}


void UIAutorisation::on_ajouterButton_clicked()
{
    FormsValidator::clear();
    FormsValidator::registerWidget(ui->lieuChargementLineEdit,FormsValidator::LIBELLE_50);
    FormsValidator::registerWidget(ui->chauffeurLineEdit,FormsValidator::LIBELLE_50);
    FormsValidator::registerWidget(ui->contactChauffeurLineEdit,FormsValidator::LIBELLE_30);
    FormsValidator::registerWidget(ui->destinationLineEdit,FormsValidator::LIBELLE_30);
    FormsValidator::registerWidget(ui->numCamionLineEdit,FormsValidator::LIBELLE_30);

    if(FormsValidator::validate()){
        Model::Autorisation c;
        c.setChauffeur(ui->chauffeurLineEdit->text().trimmed());
        c.setCamion(ui->numCamionLineEdit->text().trimmed());
        c.setContactChauffeur(ui->contactChauffeurLineEdit->text().trimmed());
        c.setLieuChargement(ui->lieuChargementLineEdit->text().trimmed());
        c.setDestination(ui->destinationLineEdit->text().trimmed());
        c.setProduit(ui->produitComboBox->currentText().trimmed());
        c.setNumeroBE(ui->numBELineEdit->text().trimmed());
        Model::Transporteur t = modelTransporteur->getById(completerIndex.data(Qt::UserRole).toInt());
        c.setTransporteur(t);
        if(ui->ajouterButton->text() == "Modifier"){
            c.setIdAutorisation(c.getIdAutorisation());
            crud->_update(&c);
        }else{
            crud->_create(&c);
        }
    }else{
        FormsValidator::showErrors();
    }
}


void UIAutorisation::on_numBELineEdit_textChanged(const QString &arg1)
{

}

