#include "adressserver.h"
#include "ui_adressserver.h"

UI::AdressServer::AdressServer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdressServer)
{
    ui->setupUi(this);

    ui->portLineEdit->setEnabled(false);

    if(!settings.value("host").toString().isEmpty() && !settings.value("port").toString().isEmpty()){

        ipAdress = settings.value("host").toString();
        port     = settings.value("port").toString();

        ui->serverIPLineEdit->setText(ipAdress);
        ui->portLineEdit->setText(port);
    }

    connect(crud->getHttpObject(),&HttpRequest::requestErrors,this,&UI::AdressServer::httpErrors);
    connect(crud->getHttpObject(),&HttpRequest::requestSuccess,this,&UI::AdressServer::httpResponse);
}

UI::AdressServer::~AdressServer()
{
    delete ui;
}

void UI::AdressServer::httpResponse(QMap<QString, QByteArray> response)
{
    if(response.firstKey() == Utils::server() + "test.php"){
        QJsonObject obj = QJsonDocument::fromJson(response.first()).object();
        QString r = obj["Response"].toString();
        if(r == "Ok"){
            ui->testResultLabel->setText("Test de connexion réussie!");
            ui->testResultLabel->setStyleSheet("color: white;background-color: green;font-size: 12px;");
        }else{
            ui->testResultLabel->setText("Test de connexion echouée!");
            ui->testResultLabel->setStyleSheet("color: white;background-color: red;font-size: 12px;");
        }
        ui->testButton->setEnabled(true);
        ui->testResultLabel->setVisible(true);
    }
}

void UI::AdressServer::httpErrors(QString error)
{
    ui->testButton->setEnabled(true);
    ui->testResultLabel->setText(error);
    ui->testResultLabel->setVisible(true);
    ui->testResultLabel->setStyleSheet("color: white;background-color: red;font-size: 12px;");
}

void UI::AdressServer::on_validerButton_clicked()
{
    settings.setValue("host",ui->serverIPLineEdit->text().trimmed());
    settings.setValue("port",ui->portLineEdit->text().trimmed());
    close();
}

void UI::AdressServer::on_testButton_clicked()
{
    settings.setValue("host",ui->serverIPLineEdit->text().trimmed());
    settings.setValue("port",ui->portLineEdit->text().trimmed());
    ui->testButton->setEnabled(false);
    crud->query("test.php");
}

void UI::AdressServer::on_quitterButton_clicked()
{
    close();
}

void UI::AdressServer::on_portLineEdit_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    ui->testResultLabel->setVisible(false);
}

void UI::AdressServer::on_serverIPLineEdit_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    ui->testResultLabel->setVisible(false);
}
