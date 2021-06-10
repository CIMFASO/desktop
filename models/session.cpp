#include "session.h"

Model::Session::Session()
{

}

int Model::Session::getIdSession() const
{
    return idSession;
}

void Model::Session::setIdSession(int value)
{
    idSession = value;
}

QString Model::Session::getDebut() const
{
    return debut;
}

void Model::Session::setDebut(const QString &value)
{
    debut = value;
}

QString Model::Session::getFin() const
{
    return fin;
}

void Model::Session::setFin(const QString &value)
{
    fin = value;
}

Model::User Model::Session::getUser() const
{
    return user;
}

void Model::Session::setUser(const Model::User &value)
{
    user = value;
}

QUrlQuery Model::Session::toUrlQuery() const
{
    QUrlQuery query;
    query.addQueryItem("idsession",QString::number(idSession));
    query.addQueryItem("debut",debut);
    query.addQueryItem("fin",fin);
    query.addQueryItem("iduser",QString::number(user.getIdUser()));
    query.addQueryItem("login",user.getLogin());

    return query;
}
