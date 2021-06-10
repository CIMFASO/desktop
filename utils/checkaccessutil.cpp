#include "checkaccessutil.h"
#include <QDebug>

Model::ModuleManager CheckAccessUtil::manager;
QList<Model::UserRoles> CheckAccessUtil::roles;
QList<Model::AccessRule> CheckAccessUtil::accessList;

CheckAccessUtil::CheckAccessUtil()
{

}

bool CheckAccessUtil::isAccessAllowed(Model::Module *module, const int &roleid)
{
    for(Model::AccessRule a : accessList){
        if(a.getModule().getIdModule() == module->getIdModule()
                && a.getRole().getIdRole() == roleid){
            return a.getAccess();
        }
    }
    return false;
}

bool CheckAccessUtil::isAccessAllowed(Model::DetailsModule *detail, const int &roleid)
{
    for(Model::AccessRule a : accessList){
        if(a.getDetailModule().getIdDetail() == detail->getIdDetail()
                && a.getRole().getIdRole() == roleid){
            return a.getAccess();
        }
    }
    return false;
}

void CheckAccessUtil::addAccessRule(const Model::AccessRule &rule)
{
    accessList.append(rule);
}

void CheckAccessUtil::addUserRole(const Model::UserRoles &role)
{
    roles.append(role);
}

void CheckAccessUtil::removeAccessRuleAt(const int &index)
{
    if(index >= 0 && index < accessList.size())
        accessList.removeAt(index);
}

void CheckAccessUtil::clearAllAccessRule()
{
    if(!accessList.isEmpty())
        accessList.clear();
}

void CheckAccessUtil::clearUserRoles()
{
    if(!roles.isEmpty())
        roles.clear();
}

bool CheckAccessUtil::contains(const Model::AccessRule &rule)
{
    for(Model::AccessRule a : accessList){
        if(a.getRole().getIdRole() == rule.getRole().getIdRole()
                && a.getModule().getIdModule() == rule.getModule().getIdModule()
                && a.getDetailModule().getIdDetail() == rule.getDetailModule().getIdDetail()){
                return true;
                break;
        }
    }
    return false;
}

QList<Model::AccessRule> CheckAccessUtil::loadAllowedRules(const int &iduser)
{
    QList<Model::AccessRule> list;
    for(Model::AccessRule a : accessList){
        if(a.getRole().getIdRole() == iduser && a.getAccess() == true)
            list.append(a);
    }
    return list;
}

QList<Model::UserRoles> CheckAccessUtil::getUserRoles()
{
    return roles;
}
QList<Model::AccessRule> CheckAccessUtil::getAccessList()
{
    return accessList;
}

void CheckAccessUtil::setAccessList(const QList<Model::AccessRule> &value)
{
    accessList = value;
}

bool CheckAccessUtil::checkAccessByLabel(Model::Module module, const int &roleid)
{
    for(Model::AccessRule a : accessList){
        for(Model::Module *m : manager.getListModule()){
            if(m->getIdModule() == a.getModule().getIdModule() && a.getRole().getIdRole() == roleid
                    && m->getIntitule() == module.getIntitule()){
                return true;
            }
        }
    }
    return false;
}
bool CheckAccessUtil::checkAccessByLabel(Model::DetailsModule details, const int &roleid)
{
    for(Model::AccessRule a : accessList){
        for(Model::DetailsModule *d : manager.getListDetailModule()){
            if(d->getIdDetail() == a.getDetailModule().getIdDetail() && a.getRole().getIdRole() == roleid
                    && d->getIntitule() == details.getIntitule()){
                return true;
            }
        }
    }
    return false;
}
