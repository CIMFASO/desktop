#include "transporteur.h"

namespace Model {
Transporteur::Transporteur() : tva(0),bic(0),retNat(0),retInt(0)
{

}

QUrlQuery Transporteur::toUrlQuery() const
{
    QUrlQuery query;
    query.addQueryItem("id",QString::number(idTransp));
    query.addQueryItem("nom",nom);
    query.addQueryItem("code",code);
    query.addQueryItem("type",type);
    query.addQueryItem("telephone",telephone);
    query.addQueryItem("tva",tva ? "1" : "0");
    query.addQueryItem("bic",bic ? "1" : "0");
    query.addQueryItem("retint",retInt ? "1" : "0");
    query.addQueryItem("retnat",retNat ? "1" : "0");
    return query;
}

int Transporteur::getId() const
{
    return idTransp;
}

QString Transporteur::getNom() const
{
    return nom;
}

void Transporteur::setNom(const QString &value)
{
    nom = value;
}

QString Transporteur::getCode() const
{
    return code;
}

void Transporteur::setCode(const QString &value)
{
    code = value;
}

QString Transporteur::getTelephone() const
{
    return telephone;
}

void Transporteur::setTelephone(const QString &value)
{
    telephone = value;
}

QString Transporteur::getLabel() const
{
    return nom;
}

int Transporteur::getIdTransp() const
{
    return idTransp;
}

void Transporteur::setIdTransp(int value)
{
    idTransp = value;
}

QString Transporteur::getType() const
{
    return type;
}

void Transporteur::setType(const QString &value)
{
    type = value;
}

bool Transporteur::getTva() const
{
    return tva;
}

void Transporteur::setTva(bool value)
{
    tva = value;
}

bool Transporteur::getBic() const
{
    return bic;
}

void Transporteur::setBic(bool value)
{
    bic = value;
}

bool Transporteur::getRetNat() const
{
    return retNat;
}

void Transporteur::setRetNat(bool value)
{
    retNat = value;
}

bool Transporteur::getRetInt() const
{
    return retInt;
}

void Transporteur::setRetInt(bool value)
{
    retInt = value;
}

}
