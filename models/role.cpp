#include "role.h"

namespace Model {
Role::Role()
{

}

int Role::getIdRole() const
{
    return idRole;
}

void Role::setIdRole(int value)
{
    idRole = value;
}

QString Role::getLibelle() const
{
    return libelle;
}

void Role::setLibelle(const QString &value)
{
    libelle = value;
}

bool Role::getStatut() const
{
    return statut;
}

void Role::setStatut(bool value)
{
    statut = value;
}

QString Role::getCode() const
{
    return code;
}

void Role::setCode(const QString &value)
{
    code = value;
}

QUrlQuery Role::toUrlQuery() const
{
    QUrlQuery query;
    query.addQueryItem("idrole",QString::number(idRole));
    query.addQueryItem("code",code);
    query.addQueryItem("libelle",libelle);
    query.addQueryItem("statut",statut ? "true" : "false");
    return query;
}
}
