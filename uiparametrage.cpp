#include "uiparametrage.h"
#include "ui_parametrage.h"
#include "uitransporteurlistview.h"
#include "uidestinationlistview.h"
#include "uitaxeslistview.h"
#include "uiparamsroles.h"
#include "utils/checkaccessutil.h"

UI::Parametrage::Parametrage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Parametrage)
{
    ui->setupUi(this);
    on_tabWidget_currentChanged(0);
    Model::ModuleManager manager;
    for(Model::UserRoles r : CheckAccessUtil::getUserRoles())
    {
        ui->tabWidget->setTabVisible(0,CheckAccessUtil::isAccessAllowed(manager.getDetailModuleById(Model::ModuleManager::ParametrageTransporteur),r.getRole().getIdRole()));
        ui->tabWidget->setTabVisible(1,CheckAccessUtil::isAccessAllowed(manager.getDetailModuleById(Model::ModuleManager::ParametrageDestination),r.getRole().getIdRole()));
        ui->tabWidget->setTabVisible(2,CheckAccessUtil::isAccessAllowed(manager.getDetailModuleById(Model::ModuleManager::ParametrageTaxes),r.getRole().getIdRole()));
        ui->tabWidget->setTabVisible(3,CheckAccessUtil::isAccessAllowed(manager.getDetailModuleById(Model::ModuleManager::ParametrageGroupesUtilisateurs),r.getRole().getIdRole()));
    }
}

UI::Parametrage::~Parametrage()
{
    delete ui;
}

void UI::Parametrage::on_tabWidget_currentChanged(int index)
{
    //parametres
    if(index == 0){
        if(ui->tabTransporteurs->layout()->itemAt(0) != nullptr){
            ui->tabTransporteurs->layout()->itemAt(0)->widget()->hide();
            delete ui->tabTransporteurs->layout()->takeAt(0);
        }
        UITransporteurListView *r = new UITransporteurListView(this);
        ui->tabTransporteurs->layout()->addWidget(r);
    }
    if(index == 1){
        if(ui->tabDestination->layout()->itemAt(0) != nullptr){
            ui->tabDestination->layout()->itemAt(0)->widget()->hide();
            delete ui->tabDestination->layout()->takeAt(0);
        }
        UIDestinationListView *r = new UIDestinationListView(this);
        ui->tabDestination->layout()->addWidget(r);
    }
    if(index == 2){
        if(ui->tabTaxes->layout()->itemAt(0) != nullptr){
            ui->tabTaxes->layout()->itemAt(0)->widget()->hide();
            delete ui->tabTaxes->layout()->takeAt(0);
        }
        UITaxesListView *r = new UITaxesListView(this);
        ui->tabTaxes->layout()->addWidget(r);
    }

    if(index == 3){
        if(ui->tablGroupesUtilisateurs->layout()->itemAt(0) != nullptr){
            ui->tablGroupesUtilisateurs->layout()->itemAt(0)->widget()->hide();
            delete ui->tablGroupesUtilisateurs->layout()->takeAt(0);
        }
        UI::ParamsRoles *r = new UI::ParamsRoles(this);
        ui->tablGroupesUtilisateurs->layout()->addWidget(r);
    }
}
