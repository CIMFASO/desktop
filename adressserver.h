#ifndef ADRESSSERVER_H
#define ADRESSSERVER_H

#include <QDialog>
#include <QSettings>
#include "dao/handledata.h"
#include "models/void.h"

namespace Ui {
class AdressServer;
}

namespace UI {
class AdressServer : public QDialog,public HandleData<Model::Void>
{
    Q_OBJECT

public:
    explicit AdressServer(QWidget *parent = nullptr);
    ~AdressServer();

private slots:
    void httpResponse(QMap<QString, QByteArray>) override;
    void httpErrors(QString error);
    void on_validerButton_clicked();
    void on_testButton_clicked();
    void on_quitterButton_clicked();

    void on_portLineEdit_textChanged(const QString &arg1);

    void on_serverIPLineEdit_textChanged(const QString &arg1);

private:
    Ui::AdressServer *ui;
    QString ipAdress,port;
    QSettings settings;
};
}
#endif // ADRESSSERVER_H
