#include "signin.h"
#include "ui_signin.h"
#include "utils/checkaccessutil.h"
#include "adressserver.h"
#include <QCryptographicHash>

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    user = new Model::User();
    this->setWindowFlags(Qt::Dialog|Qt::FramelessWindowHint);
    this->setModal(true);
    ui->passwordEdit->setEchoMode(QLineEdit::Password);
    ui->loginButton->setDefault(true);
    ui->loginErrorLabel->setVisible(false);
    ui->pseudoEdit->setFocus();

    loginErrorText = "ERREUR: Nom d'utilisateur ou mot de passe incorrect. Veuillez réessayer!";

    //crud->query("sel_infos_officine.php");

    QObject::connect(crud->getHttpObject(),&HttpRequest::requestSuccess,this,&Login::httpResponse);
    QObject::connect(crud->getHttpObject(),&HttpRequest::requestErrors,this,&Login::httpErrors);
}

Login::~Login()
{
    delete ui;
    delete user;
}

void Login::httpResponse(QMap<QString, QByteArray> response)
{
    if(response.firstKey() == Utils::server() + "authentification.php")
    {
        QJsonObject object = QJsonDocument::fromJson(response.first()).object();
        QString result = object["Response"].toString();
        if(result == "correct"){
            ui->loginButton->setText("Connexion");
            ui->loginButton->setEnabled(true);
            ui->pseudoEdit->clear();
            ui->passwordEdit->clear();
            ui->pseudoEdit->setFocus();
            QSettings settings;
            settings.beginGroup("LOGIN");
            settings.setValue("iduser",object["iduser"].toString().toInt());
            settings.setValue("idrole",object["idrole"].toString().toInt());
            settings.setValue("nom",object["nom"].toString());
            settings.setValue("rolecode",object["rolecode"].toString());
            settings.setValue("prenom",object["prenom"].toString());
            settings.setValue("login",object["login"].toString());
            settings.endGroup();
            selectUserAccessRules();
        }else if(result == "mauvais"){
            ui->loginButton->setText("Connexion");
            ui->passwordEdit->clear();
            ui->passwordEdit->setFocus();
            ui->loginErrorLabel->setVisible(true);
            ui->loginButton->setEnabled(true);
            paramsLoaded = false;
            CheckAccessUtil::clearUserRoles();
            CheckAccessUtil::clearAllAccessRule();
        }
    }

    if(response.firstKey() == Utils::server() + "sel_rule_by_id.php?iduser="+QString::number(Utils::currentUserId()))
    {
        QJsonArray array = QJsonDocument::fromJson(response.first()).array();
        for (int i = 0; i < array.size(); ++i) {
            QJsonObject obj = array.at(i).toObject();
            Model::Module module;
            module.setIdModule(obj["IDMODULE"].toString().toInt());
            Model::DetailsModule detail;
            detail.setIdDetail(obj["IDDETAILSMODULE"].toString().toInt());
            Model::Role role;
            role.setIdRole(obj["IDROLE"].toString().toInt());
            Model::AccessRule rule;
            rule.setRole(role);
            rule.setModule(module);
            rule.setDetailModule(detail);
            rule.setAccess(obj["ACCESS"].toString().toInt() == 1 ? true : false);
            CheckAccessUtil::addAccessRule(rule);
        }      
    }

    if(response.firstKey() == Utils::server() + "sel_user_roles_by_id.php?iduser="+QString::number(Utils::currentUserId()))
    {
        CheckAccessUtil::clearUserRoles();
        QJsonArray array = QJsonDocument::fromJson(response.first()).array();
        for (int i = 0; i < array.size(); ++i) {
            QJsonObject obj = array.at(i).toObject();
            Model::UserRoles uRole;
            Model::Role role;
            Model::User user;
            role.setIdRole(obj["IDROLE"].toString().toInt());
            role.setCode(obj["CODE"].toString());
            role.setLibelle(obj["LIBELLE"].toString());
            user.setIdUser(obj["ID_USER"].toString().toInt());
            user.setNom(obj["NOM_USER"].toString());
            user.setLogin(obj["LOGIN"].toString());
            user.setPrenom(obj["PRENOM_USER"].toString());
            user.setTelephone(obj["TELEPHONE"].toString());
            uRole.setRole(role);
            uRole.setUser(user);
            CheckAccessUtil::addUserRole(uRole);
        }
    }

    if(response.firstKey() == Utils::server() + "sel_infos_officine.php")
    {
        QJsonArray array = QJsonDocument::fromJson(response.first()).array();

        for (int i = 0; i < array.count(); ++i) {
            QJsonObject obj = array.at(i).toObject();
            QSettings settings;
            settings.beginGroup("OFFICINE");
            settings.setValue("idofficine",obj["idofficine"].toInt());
            settings.setValue("raisonsociale",obj["raison_sociale"].toString());
            settings.setValue("responsable",obj["nom_responsable"].toString());
            settings.setValue("devise",obj["devise"].toString());
            settings.setValue("ifu",obj["num_ifu"].toString());
            settings.setValue("rccm",obj["num_rccm"].toString());
            settings.setValue("cnss",obj["num_cnss"].toString());
            settings.setValue("compte",obj["num_compte"].toString());
            settings.setValue("localisation",obj["localisation"].toString());
            settings.setValue("adressepostale",obj["adresse_postale"].toString());
            settings.setValue("tel1",obj["telephone1"].toString());
            settings.setValue("tel2",obj["telephone2"].toString());
            settings.setValue("signature",obj["signature_facture"].toString());
            settings.setValue("email",obj["email"].toString());
            settings.setValue("regimefiscal",obj["regime_fiscal"].toString());
            settings.setValue("divisionfiscale",obj["division_fiscale"].toString());
            settings.endGroup();
            paramsLoaded = true;
        }
    }

    if(!CheckAccessUtil::getAccessList().isEmpty() && !CheckAccessUtil::getUserRoles().isEmpty()){
        emit rulesLoaded();
        this->accept();
    }
}

void Login::httpErrors(QString error)
{
    ui->loginErrorLabel->setText(error);
    ui->loginErrorLabel->setVisible(true);
    ui->loginButton->setEnabled(true);
    ui->loginButton->setText("Connexion");
}

void Login::on_pushButton_clicked(bool checked)
{
    Q_UNUSED(checked);
    qApp->quit();
}

void Login::on_loginButton_clicked()
{
    ui->loginButton->setEnabled(false);
    QString nom = ui->pseudoEdit->text().trimmed();
    QString mdp = ui->passwordEdit->text().trimmed();
    if(nom.isEmpty() || mdp.isEmpty()){
        ui->loginErrorLabel->setText(loginErrorText);
        ui->loginErrorLabel->setVisible(true);
        ui->loginButton->setEnabled(true);
        paramsLoaded = false;
    }else{
        user->setLogin(nom);
        user->setPassword(QCryptographicHash::hash(mdp.toUtf8(),QCryptographicHash::Sha256).toHex());
        crud->query("authentification.php",HttpRequest::POST,user);
        ui->loginButton->setText("Connexion en cours...");
    }
}

void Login::on_passwordEdit_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    ui->loginErrorLabel->setVisible(false);
}

void Login::on_pseudoEdit_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    ui->loginErrorLabel->setVisible(false);
}

void Login::on_mdpForgetButton_clicked()
{

}

void Login::selectUserAccessRules()

{
    crud->query("sel_rule_by_id.php?iduser="+QString::number(Utils::currentUserId()));
    crud->query("sel_user_roles_by_id.php?iduser="+QString::number(Utils::currentUserId()));
}

void Login::on_ipButton_clicked()
{
     UI::AdressServer *a = new UI::AdressServer();
     a->exec();
}
