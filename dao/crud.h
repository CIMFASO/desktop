#ifndef CRUD_H
#define CRUD_H

#include <QUrl>
#include <QObject>
#include <QSettings>
#include <QUrlQuery>
#include "utils/httprequest.h"
#include "utils.h"

template<class T>
class CRUD : public QObject
{
public:
    CRUD(){
        http = new HttpRequest;
        //http = new Server;
        //http->connectToHost();

    };
    ~CRUD(){
        delete http;
    };

    void _create(const T* t)
    {   
        http->post(addUrl,t->toUrlQuery().toString(QUrl::FullyEncoded).toUtf8());
    };
    //update
    void _update(const T* t){
        http->post(updUrl,t->toUrlQuery().toString(QUrl::FullyEncoded).toUtf8());
    };
    //delete
    void _delete(const T* t)
    {
        http->post(delUrl,t->toUrlQuery().toString(QUrl::FullyEncoded).toUtf8());
    };
    //select
    void _select()
    {
        http->get(selUrl);
    };

    //GET
    void get(const QString &adresse){
        http->get(adresse);
    }

    //PUT
    void put(const QString &adresse,const QByteArray &data){
        http->put(adresse,data);
    }

    //DELETE
    void deleteRessource(const QString &adresse){
        http->deleteRessource(adresse);
    }

    //query
    void query(const QString serverFileName,int format = HttpRequest::GET,const T* model = nullptr)
    {
        QString url = Utils::server() + serverFileName;

        if(format == HttpRequest::GET){
            http->get(url);
        }else if(format == HttpRequest::POST){
            if(model == nullptr)
                return;
            else{
                http->post(url,model->toUrlQuery().toString(QUrl::FullyEncoded).toUtf8());
            }
        }
    }

    //overrided query by using JSON as POST parameters
    void query(const QString serverFileName, QJsonObject jsonObject)
    {
        QString url = Utils::server() + serverFileName;
        http->post(url,QJsonDocument(jsonObject).toJson(),"application/json");
    }

    void _searchByName(const QString serverFileName,const QString &name)
    {
        QString url =  Utils::server() + serverFileName;
        QUrlQuery query;
        query.addQueryItem("searchName",name);
        http->post(url,query.toString(QUrl::FullyEncoded).toUtf8());
    }

    void _searchById(const QString serverFileName,const int id)
    {
        QString url = Utils::server() + serverFileName;
        QUrlQuery query;
        query.addQueryItem("searchId",QString::number(id));
        http->post(url,query.toString(QUrl::FullyEncoded).toUtf8());
    };

    QString getAddUrl() const{ return addUrl;}
    QString getDelUrl() const{ return delUrl;}
    QString getUpdUrl() const{ return updUrl;}
    QString getSelUrl() const{ return selUrl;}

    void setAddUrl(const QString &value){ addUrl =  Utils::server() + value;}
    void setDelUrl(const QString &value){ delUrl =  Utils::server() + value;}
    void setUpdUrl(const QString &value){ updUrl =  Utils::server() + value;}
    void setSelUrl(const QString &value){ selUrl =  Utils::server() + value;}


    HttpRequest *getHttpObject() const
    {
        return http;
    }

    void setHttpObject(HttpRequest *value)
    {
        http = value;
    }

protected:
    HttpRequest *http;
    QSettings settings;
    QString addUrl,delUrl,updUrl,selUrl;
};

#endif // CRUD_H
