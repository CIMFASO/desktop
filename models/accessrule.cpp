#include "accessrule.h"


Model::AccessRule::AccessRule()
{

}

QUrlQuery Model::AccessRule::toUrlQuery() const
{
    QUrlQuery query;
    query.addQueryItem("idrole",QString::number(role.getIdRole()));
    query.addQueryItem("idmodule",QString::number(module.getIdModule()));
    query.addQueryItem("iddetailsmodule",QString::number(detailModule.getIdDetail()));
    query.addQueryItem("access",QString::number(access));
    return query;
}

bool Model::AccessRule::getAccess() const
{
    return access;
}

void Model::AccessRule::setAccess(bool value)
{
    access = value;
}

Model::Role Model::AccessRule::getRole() const
{
    return role;
}

void Model::AccessRule::setRole(const Model::Role &value)
{
    role = value;
}

Model::Module Model::AccessRule::getModule() const
{
    return module;
}

void Model::AccessRule::setModule(const Model::Module &value)
{
    module = value;
}

Model::DetailsModule Model::AccessRule::getDetailModule() const
{
    return detailModule;
}

void Model::AccessRule::setDetailModule(const Model::DetailsModule &value)
{
    detailModule = value;
}

int Model::AccessRule::getIdAccesRule() const
{
    return idAccesRule;
}

void Model::AccessRule::setIdAccesRule(int value)
{
    idAccesRule = value;
}
