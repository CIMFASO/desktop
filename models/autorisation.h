#ifndef AUTORISATION_H
#define AUTORISATION_H

#include <QUrlQuery>
#include "models/transporteur.h"

namespace Model {
class Autorisation
{
public:
    Autorisation();

    QUrlQuery toUrlQuery() const;
    int getIdAutorisation() const;
    void setIdAutorisation(int newIdAutorisation);

    const QString &getDateAutorisation() const;
    void setDateAutorisation(const QString &newDateAutorisation);

    const QString &getNumAutorisation() const;
    void setNumAutorisation(const QString &newNumAutorisation);

    const Model::Transporteur &getTransporteur() const;
    void setTransporteur(const Model::Transporteur &newTransporteur);

    const QString &getProduit() const;
    void setProduit(const QString &newProduit);

    const QString &getChauffeur() const;
    void setChauffeur(const QString &newChauffeur);

    const QString &getCamion() const;
    void setCamion(const QString &newCamion);

    const QString &getContactChauffeur() const;
    void setContactChauffeur(const QString &newContactChauffeur);

    const QString &getLieuChargement() const;
    void setLieuChargement(const QString &newLieuChargement);

    const QString &getDestination() const;
    void setDestination(const QString &newDestination);

    const QString &getNumeroBE() const;
    void setNumeroBE(const QString &newNumeroBE);

private:
    int idAutorisation;
    QString dateAutorisation;
    QString numAutorisation;
    Model::Transporteur transporteur;
    QString produit;
    QString chauffeur;
    QString camion;
    QString contactChauffeur;
    QString lieuChargement;
    QString destination;
    QString numeroBE;
};
}
#endif // AUTORISATION_H
