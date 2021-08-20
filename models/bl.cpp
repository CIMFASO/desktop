#include "bl.h"

namespace Model {

BL::BL()
{

}

int BL::getId() const
{
    return id;
}

void BL::setId(int value)
{
    id = value;
}

QString BL::getNumBL() const
{
    return numBL;
}

void BL::setNumBL(const QString &value)
{
    numBL = value;
}

QString BL::getDateBL() const
{
    return dateBL;
}

void BL::setDateBL(const QString &value)
{
    dateBL = value;
}

int BL::getProduit() const
{
    return produit;
}

void BL::setProduit(int value)
{
    produit = value;
}

int BL::getQuantite() const
{
    return quantite;
}

void BL::setQuantite(int value)
{
    quantite = value;
}

QString BL::getNomLocalite() const
{
    return nomLocalite;
}

void BL::setNomLocalite(const QString &value)
{
    nomLocalite = value;
}

QString BL::getCodeTransp() const
{
    return codeTransp;
}

void BL::setCodeTransp(const QString &value)
{
    codeTransp = value;
}

double BL::getMontantBL() const
{
    return montantBL;
}

void BL::setMontantBL(double value)
{
    montantBL = value;
}

QString BL::getStatut() const
{
    return statut;
}

void BL::setStatut(const QString &value)
{
    statut = value;
}

QUrlQuery BL::toUrlQuery() const
{
    QUrlQuery query;
    query.addQueryItem("id",QString::number(id));
    query.addQueryItem("numBl",numBL);
    query.addQueryItem("dateBl",dateBL);
    query.addQueryItem("produit",QString::number(produit));
    query.addQueryItem("nomLocalite",nomLocalite);
    query.addQueryItem("codeTransp",codeTransp);
    query.addQueryItem("montantBl",QString::number(montantBL));
    query.addQueryItem("statut",statut);
    query.addQueryItem("typeCamion",typeCamion);
    return query;
}

const QString &BL::getTypeCamion() const
{
    return typeCamion;
}

void BL::setTypeCamion(const QString &newTypeCamion)
{
    typeCamion = newTypeCamion;
}
}
