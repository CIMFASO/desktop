#include "uichargement.h"
#include "ui_uichargement.h"

UIChargement::UIChargement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UIChargement)
{
    ui->setupUi(this);
    connect(crud->getHttpObject(),&HttpRequest::requestSuccess,this,&UIChargement::httpResponse);
}

UIChargement::~UIChargement()
{
    delete ui;
}

const Model::Chargement &UIChargement::getChargement() const
{
    return chargement;
}

void UIChargement::setChargement(const Model::Chargement &newChargement)
{
    chargement = newChargement;
    crud->query("sel_autorisation.php?id="+chargement.getAutorisation().getNumAutorisation());
    ui->nAutorisationLineEdit->setText(chargement.getAutorisation().getNumAutorisation());
    ui->semiRemorqueLineEdit->setText(chargement.getSemiRemorque());
    ui->poidsNetLineEdit->setText(QString::number(chargement.getPoidsNet()));
    ui->numPeseDepartLineEdit->setText(chargement.getNumPeseeDepart());
    ui->codeNavireLineEdit->setText(chargement.getCodeNavire());
}

const QString &UIChargement::getMode() const
{
    return mode;
}

void UIChargement::setMode(const QString &newMode)
{
    mode = newMode;
    ui->validerButton->setText(mode);
}

void UIChargement::on_validerButton_clicked()
{
    FormsValidator::clear();
    FormsValidator::registerWidget(ui->nAutorisationLineEdit,FormsValidator::LIBELLE_50);
    FormsValidator::registerWidget(ui->camionTracteurLineEdit,FormsValidator::LIBELLE_30);
    FormsValidator::registerWidget(ui->semiRemorqueLineEdit,FormsValidator::LIBELLE_30);
    FormsValidator::registerWidget(ui->codeNavireLineEdit,FormsValidator::LIBELLE_30);
    FormsValidator::registerWidget(ui->numPeseDepartLineEdit,FormsValidator::LIBELLE_30);

    if(FormsValidator::validate()){
        Model::Chargement c;
        Model::Autorisation a;
        a.setIdAutorisation(ui->nAutorisationLineEdit->text().trimmed().toInt());
        c.setAutorisation(a);
        c.setSemiRemorque(ui->semiRemorqueLineEdit->text().trimmed());
        c.setCodeNavire(ui->codeNavireLineEdit->text().trimmed());
        c.setPoidsNet(ui->poidsNetLineEdit->text().trimmed().toDouble());
        c.setNumPeseeDepart(ui->numPeseDepartLineEdit->text().trimmed());
        if(mode == "Modifier"){
            c.setIdChargement(chargement.getIdChargement());
            emit update(c);
        }else{
            emit create(c);
        }
    }else{
        FormsValidator::showErrors();
    }
}


void UIChargement::on_annulerButton_clicked()
{

}

void UIChargement::httpResponse(QMap<QString, QByteArray> response)
{
    if(response.firstKey().contains(Utils::server()+"sel_autorisation.php"))
    {
        QJsonArray array = QJsonDocument::fromJson(response.first()).array();
        for (int i = 0; i < array.size(); ++i) {
            QJsonObject obj = array.at(i).toObject();
            ui->lieuChargementLineEdit->setText(obj["LIEU_CHARGEMENT"].toString());
           // ui->date->setText(obj["DATE_AUTORISATION"].toString());
            ui->transporteurLineEdit->setText(obj["NOM_TRANSPORTEUR"].toString());
            ui->contactTranspLineEdit->setText(obj["CONTACT"].toString());
            ui->chauffeurLineEdit->setText(obj["CHAUFFEUR"].toString());
            ui->contactChauffeurLineEdit->setText(obj["CONTACT_CHAUFFEUR"].toString());
            ui->destinationLineEdit->setText(obj["DESTINATION"].toString());
            ui->camionTracteurLineEdit->setText(obj["CAMION_TRACTEUR"].toString());
            ui->produitLineEdit->setText(obj["PRODUIT"].toString());
        }
    }
}

void UIChargement::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return){
        if(ui->nAutorisationLineEdit->hasFocus()){
            crud->query("sel_autorisation.php?id="+ui->nAutorisationLineEdit->text().trimmed());
        }
    }
}


void UIChargement::on_nAutorisationLineEdit_textChanged(const QString &arg1)
{
    if(arg1.isEmpty()){
        ui->lieuChargementLineEdit->clear();
        ui->transporteurLineEdit->clear();
        ui->contactChauffeurLineEdit->clear();
        ui->contactTranspLineEdit->clear();
        ui->chauffeurLineEdit->clear();
        ui->destinationLineEdit->clear();
        ui->camionTracteurLineEdit->clear();
        ui->produitLineEdit->clear();
    }
}

