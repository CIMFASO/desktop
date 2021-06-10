#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QHttpMultiPart>
#include <QJsonObject>
#include <QObject>
#include <QMap>

class HttpRequest : public QObject
{
    Q_OBJECT
public:
    explicit HttpRequest(QObject *parent=0);
    ~HttpRequest();
public slots:
    void handleRequestErrors(QNetworkReply::NetworkError error);
    void uploadProgress(qint64 bytesSent, qint64 bytesTotal);
    void httpNeworkReply(QString id);
signals:
    void uploading(double progress);
    void requestSuccess(QMap<QString,QByteArray>);
    void requestErrors(QString);

public:
    void post(const QString &adresse, QByteArray params,QString header = "application/x-www-form-urlencoded");
    void post(const QString &adresse, QHttpMultiPart *multipart);
    void get(const QString &adresse);
    void put(const QString &adresse, const QByteArray &data);
    void deleteRessource(const QString &adresse);
    void setReplies(QString key, QNetworkReply* reply);
    QNetworkReply* takeReply(const QString &id);
    QHash<QString, QNetworkReply*> getReplies();
    void writeToLogFile(QString data);

    enum QueryFormat{GET = 0,POST};
private:
    QNetworkAccessManager *manager;
    QHash<QString, QNetworkReply*> replies;
};

#endif // HTTPREQUEST_H
