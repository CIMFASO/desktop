#include "autorisation.h"

namespace Model {
Autorisation::Autorisation()
{

}
QUrlQuery Autorisation::toUrlQuery() const
{
    QUrlQuery query;
    query.addQueryItem("idautorisation",QString::number(idAutorisation));
    query.addQueryItem("numautorisation",numAutorisation);
    query.addQueryItem("codetransp",transporteur.getCode());
    query.addQueryItem("produit",produit);
    query.addQueryItem("chauffeur",chauffeur);
    query.addQueryItem("contact",contactChauffeur);
    query.addQueryItem("destination",destination);
    query.addQueryItem("camion",camion);
    query.addQueryItem("numbe",numeroBE);
    query.addQueryItem("lieu",lieuChargement);
    query.addQueryItem("date",dateAutorisation);
    return query;
}

int Autorisation::getIdAutorisation() const
{
    return idAutorisation;
}

void Autorisation::setIdAutorisation(int newIdAutorisation)
{
    idAutorisation = newIdAutorisation;
}

const QString &Autorisation::getDateAutorisation() const
{
    return dateAutorisation;
}

void Autorisation::setDateAutorisation(const QString &newDateAutorisation)
{
    dateAutorisation = newDateAutorisation;
}

const QString &Autorisation::getNumAutorisation() const
{
    return numAutorisation;
}

void Autorisation::setNumAutorisation(const QString &newNumAutorisation)
{
    numAutorisation = newNumAutorisation;
}

const Model::Transporteur &Autorisation::getTransporteur() const
{
    return transporteur;
}

void Autorisation::setTransporteur(const Model::Transporteur &newTransporteur)
{
    transporteur = newTransporteur;
}

const QString &Autorisation::getProduit() const
{
    return produit;
}

void Autorisation::setProduit(const QString &newProduit)
{
    produit = newProduit;
}

const QString &Autorisation::getChauffeur() const
{
    return chauffeur;
}

void Autorisation::setChauffeur(const QString &newChauffeur)
{
    chauffeur = newChauffeur;
}

const QString &Autorisation::getCamion() const
{
    return camion;
}

void Autorisation::setCamion(const QString &newCamion)
{
    camion = newCamion;
}

const QString &Autorisation::getContactChauffeur() const
{
    return contactChauffeur;
}

void Autorisation::setContactChauffeur(const QString &newContactChauffeur)
{
    contactChauffeur = newContactChauffeur;
}

const QString &Autorisation::getLieuChargement() const
{
    return lieuChargement;
}

void Autorisation::setLieuChargement(const QString &newLieuChargement)
{
    lieuChargement = newLieuChargement;
}

const QString &Autorisation::getDestination() const
{
    return destination;
}

void Autorisation::setDestination(const QString &newDestination)
{
    destination = newDestination;
}

const QString &Autorisation::getNumeroBE() const
{
    return numeroBE;
}

void Autorisation::setNumeroBE(const QString &newNumeroBE)
{
    numeroBE = newNumeroBE;
}

}
