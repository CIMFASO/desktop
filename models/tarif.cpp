#include "tarif.h"

Tarif::Tarif()
{

}

int Tarif::getId() const
{
    return id;
}

void Tarif::setId(int newId)
{
    id = newId;
}

const Model::Ville &Tarif::getDepart() const
{
    return depart;
}

void Tarif::setDepart(const Model::Ville &newDepart)
{
    depart = newDepart;
}

const Model::Ville &Tarif::getInterm() const
{
    return interm;
}

void Tarif::setInterm(const Model::Ville &newInterm)
{
    interm = newInterm;
}

const Model::Ville &Tarif::getDestination() const
{
    return destination;
}

void Tarif::setDestination(const Model::Ville &newDestination)
{
    destination = newDestination;
}

double Tarif::getTarif1() const
{
    return tarif1;
}

void Tarif::setTarif1(double newTarif1)
{
    tarif1 = newTarif1;
}

double Tarif::getTarif2() const
{
    return tarif2;
}

void Tarif::setTarif2(double newTarif2)
{
    tarif2 = newTarif2;
}

QUrlQuery Tarif::toUrlQuery() const
{
    QUrlQuery q;
    q.addQueryItem("id",QString::number(id));
    q.addQueryItem("id_depart",QString::number(depart.getId()));
    q.addQueryItem("id_interm",QString::number(interm.getId()));
    q.addQueryItem("id_destination",QString::number(destination.getId()));
    q.addQueryItem("tarif1",QString::number(tarif1));
    q.addQueryItem("tarif2",QString::number(tarif2));
    return q;
}
