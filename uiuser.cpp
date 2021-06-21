#include "uiuser.h"
#include "ui_user.h"
#include "utils/messagebox.h"
#include "utils/contextmenu.h"
#include "utils/checkaccessutil.h"
#include "utils/tableviewdata.h"
#include "utils/formsvalidator.h"

namespace UI {

    User::User(QWidget *parent) : QDialog(parent),
        ui(new Ui::User)
    {
        ui->setupUi(this);
        model = new QStandardItemModel(this);
        moduleManager = new Model::ModuleManager();
        spinner= new WaitingSpinnerWidget(ui->usertableView,true);
        spinner->start();
        delegate=new CustomDelegate(ui->usertableView);
        ui->usertableView->setItemDelegate(delegate);

        ui->errorLabel->setVisible(false);

        crud->setAddUrl("add_user.php");
        crud->setDelUrl("del_user.php");
        crud->setUpdUrl("upd_user.php");
        crud->setSelUrl("sel_user.php");

        ui->usertableView->setModel(model);

        crud->_select();
        //ui->ajouterpushButton->setVisible(CheckAccessUtil::isAccessAllowed(new Model::DetailsModule(new Model::Module("Utilisateurs"),"Ajouter")));

        QObject::connect(delegate,&CustomDelegate::updButtonClicked,this,&UI::User::slotUpdate);
        QObject::connect(delegate,&CustomDelegate::delButtonClicked,this,&UI::User::slotDelete);
        //QObject::connect(contextMenu,SIGNAL(deleteTriggered()),this,SLOT(slotDelete()));
        //QObject::connect(contextMenu,SIGNAL(updateTriggered()),this,SLOT(slotUpdate()));
        QObject::connect(crud->getHttpObject(),SIGNAL(requestSuccess(QMap<QString,QByteArray>)),this,SLOT(httpResponse(QMap<QString,QByteArray>)));


    }

    User::~User()
    {
        delete ui;
        delete moduleManager;
    }

    void User::slotUpdate(const QModelIndex &index)
    {
        int r = QMessageBox::warning(this,"Attention","Êtes-vous sûr de bien vouloir modifier cet utilisateur ? ",QMessageBox::Yes|QMessageBox::No);
        if(r == QMessageBox::Yes){
            idUser = index.sibling(index.row(),0).data().toInt();
            ui->ajouterpushButton->setText("Modifier");
            ui->nomLineEdit->setText(index.sibling(index.row(),1).data().toString());
            ui->prenomsLineEdit->setText(index.sibling(index.row(),2).data().toString());
            ui->telephoneLineEdit->setText(index.sibling(index.row(),3).data().toString());
            ui->loginLineEdit->setText(index.sibling(index.row(),4).data().toString());
            ui->motDePasseLineEdit->setText(index.sibling(index.row(),5).data().toString());
        }
    }

    void User::slotDelete(const QModelIndex &index)
    {
        int r = QMessageBox::warning(this,"Attention","Êtes-vous sûr de bien vouloir supprimer cet utilisateur ? ",QMessageBox::Yes|QMessageBox::No);
        if(r == QMessageBox::Yes){
            Model::User *user = new Model::User;
            user->setIdUser(index.sibling(index.row(),0).data().toInt());
            crud->_delete(user);
            delete user;
        }
    }

    void User::httpResponse(QMap<QString, QByteArray> response)
    {

        if(response.firstKey() == crud->getAddUrl() || response.firstKey() == crud->getDelUrl() || response.firstKey()==crud->getUpdUrl()){
            QJsonObject object = QJsonDocument::fromJson(response.first()).object();
            QString result = object["Response"].toString();
            result == "Ok" ? MessageBox::success(this) : MessageBox::error(this);
            crud->_select();
            clearFields();
            ui->ajouterpushButton->setText("Ajouter");

        }

        if(response.firstKey() == crud->getSelUrl()){
            model->clear();
            QJsonArray array = QJsonDocument::fromJson(response.first()).array();
            QStringList headers;
            QList<int> hiddens = {0};
            QList<QStringList> data;
            delegate->setCustomColumn(5);
            headers << "ID" << "NOM" << "PRENOM"<<"TELEPHONE"<<"LOGIN"<<"ACTIONS";
            for (int i = 0; i < array.size(); ++i) {
                QJsonObject obj = array.at(i).toObject();
                QStringList items;
                items << QString::number(obj["iduser"].toInt())
                      << obj["nom"].toString()
                      << obj["prenom"].toString()
                      << obj["telephone"].toString()
                      << obj["login"].toString()
                      <<"";
                data.append(items);
            }
            if(data.isEmpty()){
                if(spinner->isSpinning())
                    spinner->stop();
                spinner->setDataSourceIsEmpty(true);
                spinner->start();
            }else{
                TableViewData::setData(data,hiddens,headers,ui->usertableView,model,true);
                //statusBarInfo();// display status infos
                if(spinner->isSpinning())
                    spinner->stop();
            }

        }
    }

    void User::clearFields()
    {
        ui->ajouterpushButton->setText("Ajouter");
        ui->nomLineEdit->clear();
        ui->prenomsLineEdit->clear();
        ui->telephoneLineEdit->clear();
        ui->loginLineEdit->clear();
        ui->motDePasseLineEdit->clear();
        ui->confirmationMdpLineEdit->clear();
    }
}

void UI::User::on_ajouterpushButton_clicked()
{
    FormsValidator::registerWidget(ui->nomLineEdit,FormsValidator::NOM);
    FormsValidator::registerWidget(ui->prenomsLineEdit,FormsValidator::PRENOMS);
    FormsValidator::registerWidget(ui->telephoneLineEdit,FormsValidator::PHONE);
    FormsValidator::registerWidget(ui->loginLineEdit,FormsValidator::PRENOMS);
    //FormsValidator::registerWidget(ui->ageLineEdit,FormsValidator::AGE);
    if(FormsValidator::validate()){
        if(ui->motDePasseLineEdit->text().trimmed() != ui->confirmationMdpLineEdit->text().trimmed()){
            ui->errorLabel->setVisible(true);
            return;
        }

        Model::User *user = new Model::User();
        user->setNom(ui->nomLineEdit->text().trimmed());
        user->setPrenom(ui->prenomsLineEdit->text().trimmed());
        user->setLogin(ui->loginLineEdit->text().trimmed());
        user->setTelephone(ui->telephoneLineEdit->text().trimmed());
        user->setPassword(ui->motDePasseLineEdit->text().trimmed());

        if(ui->ajouterpushButton->text()=="Modifier"){
            user->setIdUser(idUser);
            crud->_update(user);
        }else{
            crud->_create(user);
        }
        delete user;
    }
    else {
        FormsValidator::showErrors();
    }
}

void UI::User::on_annulerpushButton_clicked()
{
    clearFields();
}

void UI::User::on_usertableView_customContextMenuRequested(const QPoint &pos)
{
    contextMenu->setupMenu(ui->usertableView,pos);
}

void UI::User::on_confirmationMdpLineEdit_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    if(ui->errorLabel->isVisible())
        ui->errorLabel->setVisible(false);
}

void UI::User::on_motDePasseLineEdit_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    if(ui->errorLabel->isVisible())
        ui->errorLabel->setVisible(false);
}
