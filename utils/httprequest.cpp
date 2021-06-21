#include "httprequest.h"
#include "utils.h"
#include <QtMath>
#include "singleton.h"
#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QTextStream>

HttpRequest::HttpRequest(QObject *parent)
{
    /*******************************************************************************                                     *
     * Cette instruction a pour but de garder la même instance de QNetworkAccesManager *
     *******************************************************************************/
    manager = &Singleton<QNetworkAccessManager>::Instance();
}

HttpRequest::~HttpRequest(){} //Destructeur vide

void HttpRequest::get(const QString &adresse)
{
    QUrl url = QUrl(adresse);
    QNetworkRequest request;
    //request.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    request.setUrl(url);
    QNetworkReply *reply = manager->get(request);
    if(!getReplies().contains(adresse))
    {
        setReplies(adresse,reply);
        connect(reply,&QNetworkReply::finished, [=]() {emit httpNeworkReply(adresse);});
        connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),this, SLOT(handleRequestErrors(QNetworkReply::NetworkError)));
    }
}

void HttpRequest::put(const QString &adresse, const QByteArray &data)
{
    QUrl url = QUrl(adresse);
    QNetworkRequest request;
    //request.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    request.setUrl(url);
    QNetworkReply *reply = manager->put(request,data);
    if(!getReplies().contains(adresse))
    {
        setReplies(adresse,reply);
        connect(reply,&QNetworkReply::finished, [=]() {emit httpNeworkReply(adresse);});
        connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),this, SLOT(handleRequestErrors(QNetworkReply::NetworkError)));
    }
}

void HttpRequest::deleteRessource(const QString &adresse)
{
    QUrl url = QUrl(adresse);
    QNetworkRequest request;
    //request.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    request.setUrl(url);
    QNetworkReply *reply = manager->deleteResource(request);
    if(!getReplies().contains(adresse))
    {
        setReplies(adresse,reply);
        connect(reply,&QNetworkReply::finished, [=]() {emit httpNeworkReply(adresse);});
        connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),this, SLOT(handleRequestErrors(QNetworkReply::NetworkError)));
    }
}

void HttpRequest::post(const QString &adresse, QByteArray params,QString header)
{
    QUrl url = QUrl(adresse);
    QNetworkRequest request;
    //request.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    request.setHeader(QNetworkRequest::ContentTypeHeader,header);
    request.setUrl(url);
    QNetworkReply *reply = manager->post(request,params);
    if(!getReplies().contains(adresse))
    {
        setReplies(adresse,reply);
        connect(reply,&QNetworkReply::finished, [=]() {emit httpNeworkReply(adresse);});
        connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),this, SLOT(handleRequestErrors(QNetworkReply::NetworkError)));
    }
}

void HttpRequest::post(const QString &adresse, QHttpMultiPart  *multipart)
{
    /*QUrl url = QUrl(adresse);
    QNetworkRequest request(url);
    //request.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    QNetworkReply *reply = manager->post(request,multipart);
    multipart->setParent(reply);
    if(!getReplies().contains(adresse))
    {
        setReplies(adresse,reply);
        connect(reply,&QNetworkReply::uploadProgress,this,&HttpRequest::uploadProgress);
        connect(reply,&QNetworkReply::finished, [=]() {emit httpNeworkReply(adresse);});
        connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),this, SLOT(handleRequestErrors(QNetworkReply::NetworkError)));
    }*/
}

void HttpRequest::uploadProgress(qint64 bytesSent,qint64 bytesTotal)
{
    if(bytesTotal != -1){
        long double progress = qCeil((long double)bytesSent/(long double)bytesTotal);
        progress *= 100;
        emit uploading(qCeil(progress));
    }
}

QHash<QString,QNetworkReply*> HttpRequest::getReplies()
{
    return replies;
}

void HttpRequest::setReplies(QString key, QNetworkReply* reply)
{
    replies.insert(key, reply);
}

QNetworkReply* HttpRequest::takeReply(const QString &id)
{
    return replies.take(id);
}

void HttpRequest::writeToLogFile(QString data)
{
    QFile file(Utils::logFilePath());
    if(file.size() > 30720000){// clear file if up to 30MB
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;
    }else{
        if (!file.open(QIODevice::WriteOnly | QIODevice::Append))
            return;
    }

    QTextStream out(&file);
    out <<"["<<QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss")<<"]" <<  data << "\n\n";

}

void HttpRequest::httpNeworkReply(QString id)
{
    QNetworkReply *reply = takeReply(id);
    if(reply->bytesAvailable()){

        QByteArray buffer = reply->readAll();

        //if(id.contains(Utils::server()+"sel_details_vente.php"))
            qDebug() << QString(buffer);

        writeToLogFile(QString(buffer));

        QMap<QString,QByteArray> map;
        map.insert(id,buffer);
        emit requestSuccess(map);
    }

    reply->deleteLater();
}

void HttpRequest::handleRequestErrors(QNetworkReply::NetworkError error)
{
    QString error_msg;
    switch (error) {
    case QNetworkReply::TimeoutError:
        error_msg = "Délai d'attente dépassé, veuillez réessayer!";
        break;
    case QNetworkReply::HostNotFoundError:
        error_msg = "Adresse introuvable, veuillez réessayer!";
        break;
    case QNetworkReply::UnknownServerError:
        error_msg = "Erreur de serveur inconnue, veuillez réessayer!";
        break;
    case QNetworkReply::UnknownNetworkError:
        error_msg = "Erreur de réseau inconnue, veuillez réessayer!";
        break;
    case QNetworkReply::ContentNotFoundError:
        error_msg = "Contenu introuvable à cette adresse, veuillez réessayer!";
        break;
    case QNetworkReply::ConnectionRefusedError:
        error_msg = "Connection refusée, veuillez réessayer!";
        break;
    case QNetworkReply::OperationCanceledError:
        error_msg = "Opération annulée, veuillez réessayer!";
        break;
    case QNetworkReply::ContentAccessDenied:
        error_msg = "Accès interdit à ce contenu, veuillez réessayer!";
        break;
    default:
        error_msg = "L'opération n'a pas pu aboutir, veuillez réessayer!";
        break;
    }
    emit requestErrors(error_msg);
}
