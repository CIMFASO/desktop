#include "uisecurite.h"
#include "ui_securite.h"
#include "uiuserslistview.h"
#include "uiusersroles.h"
#include "uiusersrights.h"
#include "utils/checkaccessutil.h"
#include "models/modulemanager.h"

UI::Securite::Securite(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Securite)
{
    ui->setupUi(this);
    on_tabWidget_currentChanged(0);
    //handleUserRights();
}

UI::Securite::~Securite()
{
    delete ui;
}

void UI::Securite::handleUserRights()
{
    Model::ModuleManager manager;
    for(Model::UserRoles r : CheckAccessUtil::getUserRoles())
    {
        ui->tabWidget->setTabEnabled(0,CheckAccessUtil::isAccessAllowed(manager.getDetailModuleById(Model::ModuleManager::Securite::SecuriteUtilisateurs),r.getRole().getIdRole()));
        ui->tabWidget->setTabEnabled(1,CheckAccessUtil::isAccessAllowed(manager.getDetailModuleById(Model::ModuleManager::Securite::SecuriteGroupesUtilisateurs),r.getRole().getIdRole()));
        ui->tabWidget->setTabEnabled(2,CheckAccessUtil::isAccessAllowed(manager.getDetailModuleById(Model::ModuleManager::Securite::SecuriteDroitsAccess),r.getRole().getIdRole()));
    }
}

void UI::Securite::on_tabWidget_currentChanged(int index)
{
    if(index == 0){
        if(ui->tabUtilisateurs->layout()->itemAt(0) != nullptr){
            ui->tabUtilisateurs->layout()->itemAt(0)->widget()->hide();
            delete ui->tabUtilisateurs->layout()->takeAt(0);
        }
        UIUsersListview *s = new UIUsersListview(this);
        ui->tabUtilisateurs->layout()->addWidget(s);
    }
    else if(index == 1){
        if(ui->tabGroupes->layout()->itemAt(0) != nullptr){
            ui->tabGroupes->layout()->itemAt(0)->widget()->hide();
            delete ui->tabGroupes->layout()->takeAt(0);
        }
        UI::UsersRoles *s = new UI::UsersRoles(this);
        ui->tabGroupes->layout()->addWidget(s);
    }
    else if(index == 2){
        if(ui->tabDroits->layout()->itemAt(0) != nullptr){
            ui->tabDroits->layout()->itemAt(0)->widget()->hide();
            delete ui->tabDroits->layout()->takeAt(0);
        }
        UI::UsersRights *s = new UI::UsersRights(this);
        ui->tabDroits->layout()->addWidget(s);
    }
}
