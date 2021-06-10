#include "userroles.h"

namespace Model {
UserRoles::UserRoles()
{

}

Model::User UserRoles::getUser() const
{
    return user;
}

void UserRoles::setUser(const Model::User &value)
{
    user = value;
}

Model::Role UserRoles::getRole() const
{
    return role;
}

void UserRoles::setRole(const Model::Role &value)
{
    role = value;
}

QUrlQuery UserRoles::toUrlQuery() const
{
    QUrlQuery query;
    query.addQueryItem("iduser",QString::number(user.getIdUser()));
    query.addQueryItem("idrole",QString::number(role.getIdRole()));
    return query;
}
}
