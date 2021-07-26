#include "chargement.h"

namespace Model {
Chargement::Chargement()
{

}

int Chargement::getIdChargement() const
{
    return idChargement;
}

void Chargement::setIdChargement(int newIdChargement)
{
    idChargement = newIdChargement;
}

const QString &Chargement::getCodeNavire() const
{
    return codeNavire;
}

void Chargement::setCodeNavire(const QString &newCodeNavire)
{
    codeNavire = newCodeNavire;
}

const double &Chargement::getPoidsNet() const
{
    return poidsNet;
}

void Chargement::setPoidsNet(const double &newPoidsNet)
{
    poidsNet = newPoidsNet;
}

const QString &Chargement::getNumPeseeDepart() const
{
    return numPeseeDepart;
}

void Chargement::setNumPeseeDepart(const QString &newNumPeseeDepart)
{
    numPeseeDepart = newNumPeseeDepart;
}

const QString &Chargement::getSemiRemorque() const
{
    return semiRemorque;
}

void Chargement::setSemiRemorque(const QString &newSemiRemorque)
{
    semiRemorque = newSemiRemorque;
}

const QString &Chargement::getPoidsLivre() const
{
    return poidsLivre;
}

void Chargement::setPoidsLivre(const QString &newPoidsLivre)
{
    poidsLivre = newPoidsLivre;
}

const QString &Chargement::getDateLivraison() const
{
    return dateLivraison;
}

void Chargement::setDateLivraison(const QString &newDateLivraison)
{
    dateLivraison = newDateLivraison;
}

const QString &Chargement::getDateChargement() const
{
    return dateChargement;
}

void Chargement::setDateChargement(const QString &newDateChargement)
{
    dateChargement = newDateChargement;
}

QUrlQuery Chargement::toUrlQuery() const
{
    QUrlQuery query;
    query.addQueryItem("idchargement",QString::number(idChargement));
    query.addQueryItem("numchargement",numeroChargement);
    query.addQueryItem("idautorisation",QString::number(autorisation.getIdAutorisation()));
    query.addQueryItem("codenavire",codeNavire);
    query.addQueryItem("poidsnet",QString::number(poidsNet));
    query.addQueryItem("numpesee",numPeseeDepart);
    query.addQueryItem("semiremorque",semiRemorque);
    query.addQueryItem("poidsnetlivraison",poidsLivre);
    query.addQueryItem("datelivraison",dateLivraison);
    query.addQueryItem("date",dateChargement);
    return query;
}

const Model::Autorisation &Chargement::getAutorisation() const
{
    return autorisation;
}

void Chargement::setAutorisation(const Model::Autorisation &newAutorisation)
{
    autorisation = newAutorisation;
}

const QString &Chargement::getNumeroChargement() const
{
    return numeroChargement;
}

void Chargement::setNumeroChargement(const QString &newNumeroChargement)
{
    numeroChargement = newNumeroChargement;
}

}
