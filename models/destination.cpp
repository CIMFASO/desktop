#include "destination.h"

namespace Model {
Destination::Destination()
{

}

int Destination::getIdDest() const
{
    return idDest;
}

void Destination::setIdDest(int value)
{
    idDest = value;
}

QString Destination::getNom() const
{
    return nom;
}

void Destination::setNom(const QString &value)
{
    nom = value;
}

double Destination::getTarif() const
{
    return tarif;
}

void Destination::setTarif(double value)
{
    tarif = value;
}

QUrlQuery Destination::toUrlQuery() const
{
    QUrlQuery query;
    query.addQueryItem("id",QString::number(idDest));
    query.addQueryItem("nom",nom);
    query.addQueryItem("tarif",QString::number(tarif));
    query.addQueryItem("tarif_plat",QString::number(tarifPlat));
    return query;
}

QString Destination::getLabel() const
{
    return nom;
}

int Destination::getId() const
{
    return idDest;
}

double Destination::getTarifPlat() const
{
    return tarifPlat;
}

void Destination::setTarifPlat(double newTarifPlat)
{
    tarifPlat = newTarifPlat;
}
}
