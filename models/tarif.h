#ifndef TARIF_H
#define TARIF_H

#include "models/ville.h"

class Tarif
{
public:
    Tarif();

    int getId() const;
    void setId(int newId);

    const Model::Ville &getDepart() const;
    void setDepart(const Model::Ville &newDepart);

    const Model::Ville &getInterm() const;
    void setInterm(const Model::Ville &newInterm);

    const Model::Ville &getDestination() const;
    void setDestination(const Model::Ville &newDestination);

    double getTarif1() const;
    void setTarif1(double newTarif1);

    double getTarif2() const;
    void setTarif2(double newTarif2);

    QUrlQuery toUrlQuery() const;
private:
    int id;
    Model::Ville depart;
    Model::Ville interm;
    Model::Ville destination;
    double tarif1;
    double tarif2;
};

#endif // TARIF_H
