#ifndef USERROLES_H
#define USERROLES_H

#include "models/user.h"
#include "models/role.h"

namespace Model {
class UserRoles
{
public:
    UserRoles();

    Model::User getUser() const;
    void setUser(const Model::User &value);

    Model::Role getRole() const;
    void setRole(const Model::Role &value);

    QUrlQuery toUrlQuery() const;
private:
    Model::User user;
    Model::Role role;
};
}
#endif // USERROLES_H
