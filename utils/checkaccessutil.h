#ifndef CHECKACCESSUTIL_H
#define CHECKACCESSUTIL_H

#include <QObject>
#include <QList>
#include "models/accessrule.h"
#include "models/userroles.h"
#include "utils.h"
#include "models/modulemanager.h"

class CheckAccessUtil : public QObject
{
    Q_OBJECT
public:
    CheckAccessUtil();

    static bool isAccessAllowed(Model::Module *module, const int &roleid);
    static bool isAccessAllowed(Model::DetailsModule *detail, const int &roleid);
    static void addAccessRule(const Model::AccessRule &rule);
    static void addUserRole(const Model::UserRoles &role);
    static void removeAccessRuleAt(const int &index);
    static void clearAllAccessRule();
    static void clearUserRoles();
    static bool contains(const Model::AccessRule &rule);
    static QList<Model::AccessRule> loadAllowedRules(const int &iduser);
    static QList<Model::AccessRule> getAccessList();
    static void setAccessList(const QList<Model::AccessRule> &value);
    static bool checkAccessByLabel(Model::Module module, const int &roleid);
    static bool checkAccessByLabel(Model::DetailsModule details, const int &roleid);
    static QList<Model::UserRoles> getUserRoles();
private:
    static Model::ModuleManager manager;
    static QList<Model::AccessRule> accessList;
    static QList<Model::UserRoles> roles;

};

#endif // CHECKACCESSUTIL_H
