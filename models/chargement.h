#ifndef CHARGEMENT_H
#define CHARGEMENT_H

#include <QUrlQuery>
#include "models/transporteur.h"
#include "models/autorisation.h"

namespace Model {
class Chargement
{
public:
    Chargement();

    int getIdChargement() const;
    void setIdChargement(int newIdChargement);

    const QString &getCodeNavire() const;
    void setCodeNavire(const QString &newCodeNavire);

    const double &getPoidsNet() const;
    void setPoidsNet(const double &newPoidsNet);

    const QString &getNumPeseeDepart() const;
    void setNumPeseeDepart(const QString &newNumPeseeDepart);

    const QString &getSemiRemorque() const;
    void setSemiRemorque(const QString &newSemiRemorque);

    const QString &getPoidsLivre() const;
    void setPoidsLivre(const QString &newPoidsLivre);

    const QString &getDateLivraison() const;
    void setDateLivraison(const QString &newDateLivraison);

    const QString &getDateChargement() const;
    void setDateChargement(const QString &newDateChargement);

    QUrlQuery toUrlQuery() const;

    const Model::Autorisation &getAutorisation() const;
    void setAutorisation(const Model::Autorisation &newAutorisation);

    const QString &getNumeroChargement() const;
    void setNumeroChargement(const QString &newNumeroChargement);

private:
    int idChargement;
    Model::Autorisation autorisation;
    QString numeroChargement;
    QString codeNavire;
    double poidsNet;
    QString numPeseeDepart;
    QString semiRemorque;
    QString poidsLivre;
    QString dateLivraison;
    QString dateChargement;

};
}
#endif // CHARGEMENT_H
