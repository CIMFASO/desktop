#include "uiparamsroles.h"
#include "ui_paramsroles.h"
#include "utils/formsvalidator.h"

UI::ParamsRoles::ParamsRoles(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParamsRoles)
{
    ui->setupUi(this);
    model = new QStandardItemModel(this);
    ui->tableView->setModel(model);
    delegate=new CustomDelegate(ui->tableView);
    spinner= new WaitingSpinnerWidget(ui->tableView,true);
    spinner->start();
    ui->tableView->setItemDelegate(delegate);

    crud->setAddUrl("add_role.php");
    crud->setDelUrl("del_role.php");
    crud->setSelUrl("sel_role.php");
    crud->setUpdUrl("upd_role.php");
    crud->_select(); //select data from database

    QObject::connect(delegate,&CustomDelegate::updButtonClicked,this,&UI::ParamsRoles::slotUpdate);
    QObject::connect(delegate,&CustomDelegate::delButtonClicked,this,&UI::ParamsRoles::slotDelete);
    QObject::connect(crud->getHttpObject(),&HttpRequest::requestSuccess,this,&UI::ParamsRoles::httpResponse);
}

UI::ParamsRoles::~ParamsRoles()
{
    delete ui;
}

void UI::ParamsRoles::on_validerButton_clicked()
{
    FormsValidator::registerWidget(ui->libelleLineEdit,FormsValidator::LIBELLE_40);
    FormsValidator::registerWidget(ui->codeLineEdit,FormsValidator::CODE_GROUPE);
    if(FormsValidator::validate()){
        Model::Role *role = new Model::Role();
        role->setLibelle(ui->libelleLineEdit->text().trimmed());
        role->setCode(ui->codeLineEdit->text().trimmed());
        role->setStatut(true);
        if(ui->validerButton->text() == "Valider"){
            crud->_create(role);
        }else{
            role->setIdRole(idRole);
            crud->_update(role);
        }
        delete role;
    }else{
        FormsValidator::showErrors();
    }
}

void UI::ParamsRoles::on_annulerButton_clicked()
{
    ui->libelleLineEdit->clear();
}

void UI::ParamsRoles::httpResponse(QMap<QString, QByteArray> response)
{
    if(response.firstKey() == crud->getAddUrl() || response.firstKey() == crud->getDelUrl()|| response.firstKey()== crud->getUpdUrl()){
        QJsonObject object = QJsonDocument::fromJson(response.first()).object();
        QString result = object["Response"].toString();
        result == "Ok" ? MessageBox::success(this) : MessageBox::error(this);
        crud->_select();
        if(result == "Ok"){
            ui->validerButton->setText("Valider");
            on_annulerButton_clicked();//clear fields
        }
    }

    if(response.firstKey() == crud->getSelUrl()){
        model->clear();
        QJsonArray array = QJsonDocument::fromJson(response.first()).array();
        QStringList headers;
        QList<int> hiddens;
        QList<QStringList> data;
        delegate->setCustomColumn(3);
        hiddens << 0;
        headers << "ID"  << "CODE" << "LIBELLE"<<"ACTIONS";
        for (int i = 0; i < array.size(); ++i) {
            QJsonObject obj = array.at(i).toObject();
            QStringList items;
            items << QString::number(obj["IDROLE"].toString().toInt())
                  << obj["CODE"].toString()
                  << obj["LIBELLE"].toString()
                  << "";

            data.append(items);
        }
        if(data.isEmpty()){
            if(spinner->isSpinning())
                spinner->stop();
            spinner->setDataSourceIsEmpty(true);
            spinner->start();
        }else{
            TableViewData::setData(data,hiddens,headers,ui->tableView,model,true,false,{},QHeaderView::Stretch);
            //statusBarInfo();// display status infos
            if(spinner->isSpinning())
                spinner->stop();
        }
    }
}

void UI::ParamsRoles::slotDelete(const QModelIndex &index)
{
    if(MessageBox::confirmDelete(this)){
        idRole= index.sibling(index.row(),0).data().toInt();
        Model::Role *role = new Model::Role();
        role->setIdRole(idRole);
        crud->_delete(role);
    }
}

void UI::ParamsRoles::slotUpdate(const QModelIndex &index)
{
    if(MessageBox::confirmUpdate(this))
    {
        ui->validerButton->setText("Modidier");
        idRole= index.sibling(index.row(),0).data().toInt();
        ui->libelleLineEdit->setText(index.sibling(index.row(),2).data().toString());
        ui->codeLineEdit->setText(index.sibling(index.row(),1).data().toString());
    }
}
