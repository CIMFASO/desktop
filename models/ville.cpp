#include "ville.h"

namespace Model {

Ville::Ville()
{

}

int Ville::getId() const
{
    return id;
}

void Ville::setId(int newId)
{
    id = newId;
}

const QString &Ville::getNom() const
{
    return nom;
}

void Ville::setNom(const QString &newNom)
{
    nom = newNom;
}

QUrlQuery Ville::toUrlQuery() const
{
    QUrlQuery q;
    q.addQueryItem("id",QString::number(id));
    q.addQueryItem("nom",nom);
    return q;
}
}
