#include "parametreglobal.h"

namespace Model {
ParametreGlobal::ParametreGlobal()
{

}

int ParametreGlobal::getIdParam() const
{
    return idParam;
}

void ParametreGlobal::setIdParam(int value)
{
    idParam = value;
}

QString ParametreGlobal::getCode() const
{
    return code;
}

void ParametreGlobal::setCode(const QString &value)
{
    code = value;
}

Model::TypeParametreGlobal ParametreGlobal::getTypeParametre() const
{
    return typeParametre;
}

void ParametreGlobal::setTypeParametre(const Model::TypeParametreGlobal &value)
{
    typeParametre = value;
}

QString ParametreGlobal::getLibelle() const
{
    return libelle;
}

void ParametreGlobal::setLibelle(const QString &value)
{
    libelle = value;
}

QUrlQuery ParametreGlobal::toUrlQuery() const
{
    QUrlQuery query;
    query.addQueryItem("idparam",QString::number(idParam));
    query.addQueryItem("code",code);
    query.addQueryItem("idtype",QString::number(typeParametre.getIdType()));
    query.addQueryItem("libelle",libelle);
    return query;
}

QString ParametreGlobal::getLabel() const
{
    return libelle;
}

int ParametreGlobal::getId() const
{
    return idParam;
}

}
