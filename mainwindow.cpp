#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "uibl.h"
#include "uitransporteurlistview.h"
#include "uidestinationlistview.h"
#include "uifactureslistview.h"
#include "uitaxeslistview.h"
#include "uiparametrage.h"
#include "uistatsfactureslistview.h"
#include "utils/checkaccessutil.h"
#include "uisecurite.h"
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("CIMFASO - AppGestion");
    //on_actionListe_des_B_L_triggered();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::hideActions()
{
    Model::ModuleManager manager;
    for(Model::UserRoles r : CheckAccessUtil::getUserRoles())
    {
        ui->actionListe_des_B_L->setVisible(CheckAccessUtil::isAccessAllowed(manager.getModuleById(Model::ModuleManager::ListeBL),r.getRole().getIdRole()));
        ui->actionFactures->setVisible(CheckAccessUtil::isAccessAllowed(manager.getModuleById(Model::ModuleManager::Factures),r.getRole().getIdRole()));
        ui->actionSecurit->setVisible(CheckAccessUtil::isAccessAllowed(manager.getModuleById(Model::ModuleManager::Securite),r.getRole().getIdRole()));
        ui->actionEtats_Factures->setVisible(CheckAccessUtil::isAccessAllowed(manager.getModuleById(Model::ModuleManager::EtatsFactures),r.getRole().getIdRole()));
        ui->actionParam_trage->setVisible(CheckAccessUtil::isAccessAllowed(manager.getModuleById(Model::ModuleManager::Parametrage),r.getRole().getIdRole()));

        ui->actionTransporteur->setVisible(CheckAccessUtil::isAccessAllowed(manager.getDetailModuleById(Model::ModuleManager::ParametrageTransporteur),r.getRole().getIdRole()));
        ui->actionDestination->setVisible(CheckAccessUtil::isAccessAllowed(manager.getDetailModuleById(Model::ModuleManager::ParametrageDestination),r.getRole().getIdRole()));
        ui->actionTaxes->setVisible(CheckAccessUtil::isAccessAllowed(manager.getDetailModuleById(Model::ModuleManager::ParametrageTaxes),r.getRole().getIdRole()));
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    /*int r = QMessageBox::warning(this,"Attention","Une session est actuellement ouverte. Etes vous sûr de vouloir fermer ? La session ne sera pas arrêté automatiquement!",QMessageBox::Yes|QMessageBox::No);
    if(r == QMessageBox::Yes){
       //CheckAccessUtil::clearAllAccessRule();
       event->accept();
    }else
       event->ignore();*/
    event->accept();
}

void MainWindow::showWidgetInMainLayout(QWidget *w)
{
    if(ui->centralwidget->layout()->itemAt(0) != nullptr){
        ui->centralwidget->layout()->itemAt(0)->widget()->hide();
        delete ui->centralwidget->layout()->takeAt(0);
    }
    ui->centralwidget->layout()->addWidget(w);
}

void MainWindow::on_actionTaille_de_police_triggered()
{
    bool ok;
    QSettings settings;
    QFont initial = QFont(
        settings.value("fontFamily","Calibri").toString(),
        settings.value("fontSize",13).toInt(),
        settings.value("fontBold",false).toInt(),
        settings.value("fontItalic",false).toBool()
    );

    QFont ft = QFontDialog::getFont(&ok,initial,this);
    if(ok){
        QFile f(":style/style.qss");
        if(!f.exists())
            printf("Fichier introuvable");
        else{
            f.open(QFile::ReadOnly | QFile::Text);
            QTextStream ts(&f);
            QString style = "";
            style += "QWidget{font: "+QString::number(ft.pointSize())+"px '"+ft.family()+"';}";
            style += ts.readAll();
            setStyleSheet(style);
            ensurePolished();
            settings.setValue("fontFamily",ft.family());
            settings.setValue("fontSize",ft.pointSize());
            settings.setValue("fontBold",ft.bold());
            settings.setValue("fontItalic",ft.italic());
        }
    }
}



void MainWindow::on_actionListe_des_B_L_triggered()
{
    UIBL *b = new UIBL(this);
    showWidgetInMainLayout(b);
}

void MainWindow::on_actionTransporteur_triggered()
{
    UITransporteurListView *d = new UITransporteurListView(this);
    d->setWindowTitle("Transporteur");
    d->setWindowFlag(Qt::WindowType::WindowMinMaxButtonsHint);
    d->show();
}

void MainWindow::on_actionDestination_triggered()
{
    UIDestinationListView *d = new UIDestinationListView(this);
    d->setWindowTitle("Destination");
    d->setWindowFlag(Qt::WindowType::WindowMinMaxButtonsHint);
    d->show();
}

void MainWindow::on_actionFactures_triggered()
{
    UIFacturesListView *f = new UIFacturesListView(this);
    showWidgetInMainLayout(f);
}

void MainWindow::on_actionTaxes_triggered()
{
    UITaxesListView *d = new UITaxesListView(this);
    d->setWindowTitle("Taxes");
    d->setWindowFlag(Qt::WindowType::WindowMinMaxButtonsHint);
    d->show();
}

void MainWindow::on_actionDeconnexion_triggered()
{
    int r = QMessageBox::warning(this,"Attention","Etes vous sûr de vouloir vous déconnecter ?",QMessageBox::Yes|QMessageBox::No);
    if(r == QMessageBox::Yes){
        CheckAccessUtil::clearUserRoles();
        CheckAccessUtil::clearAllAccessRule();
        emit deconnexion();
    }
}

void MainWindow::on_actionParam_trage_triggered()
{
    UI::Parametrage *d = new UI::Parametrage(this);
    d->setWindowTitle("Paramétrage");
    d->setWindowFlag(Qt::WindowType::WindowMinMaxButtonsHint);
    d->show();
}

void MainWindow::on_actionSecurit_triggered()
{
    UI::Securite *d = new UI::Securite(this);
    d->setWindowTitle("Securité");
    d->setWindowFlag(Qt::WindowType::WindowMinMaxButtonsHint);
    d->show();
}

void MainWindow::on_actionEtats_Factures_triggered()
{
    UIStatsFacturesListView *f = new UIStatsFacturesListView(this);
    f->setWindowTitle("Etats des factures");
    showWidgetInMainLayout(f);
}
