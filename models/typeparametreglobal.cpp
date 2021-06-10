#include "typeparametreglobal.h"

namespace Model {
TypeParametreGlobal::TypeParametreGlobal()
{

}

QUrlQuery Model::TypeParametreGlobal::toUrlQuery() const
{
    QUrlQuery query;
    query.addQueryItem("idtype",QString::number(idType));
    query.addQueryItem("code",code);
    query.addQueryItem("libelle",libelle);
    return query;
}

QString TypeParametreGlobal::getLibelle() const
{
    return libelle;
}

void TypeParametreGlobal::setLibelle(const QString &value)
{
    libelle = value;
}

int TypeParametreGlobal::getId() const
{
    return idType;
}

QString TypeParametreGlobal::getLabel() const
{
    return libelle;
}

QString TypeParametreGlobal::getCode() const
{
    return code;
}

void TypeParametreGlobal::setCode(const QString &value)
{
    code = value;
}

int TypeParametreGlobal::getIdType() const
{
    return idType;
}

void TypeParametreGlobal::setIdType(int value)
{
    idType = value;
}


}
