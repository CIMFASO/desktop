#include "taxe.h"

namespace Model {

Taxe::Taxe(){};

int Taxe::getIdTaxe() const
{
    return idTaxe;
}

void Taxe::setIdTaxe(int value)
{
    idTaxe = value;
}

QString Taxe::getLibelle() const
{
    return libelle;
}

void Taxe::setLibelle(const QString &value)
{
    libelle = value;
}

double Taxe::getTaux() const
{
    return taux;
}

void Taxe::setTaux(double value)
{
    taux = value;
}

QUrlQuery Model::Taxe::toUrlQuery() const
{
    QUrlQuery query;
    query.addQueryItem("id",QString::number(idTaxe));
    query.addQueryItem("libelle",libelle);
    query.addQueryItem("taux",QString::number(taux));
    return query;
}
}
