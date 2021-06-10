#ifndef ACCESSRULE_H
#define ACCESSRULE_H

#include <QObject>
#include "models/module.h"
#include "models/userroles.h"
#include "models/detailsmodule.h"

namespace Model {
    class AccessRule
    {
    public:
        AccessRule();

        QUrlQuery toUrlQuery() const;
        int getIdAccesRule() const;
        void setIdAccesRule(int value);

        Model::DetailsModule getDetailModule() const;
        void setDetailModule(const Model::DetailsModule &value);

        Model::Module getModule() const;
        void setModule(const Model::Module &value);

        bool getAccess() const;
        void setAccess(bool value);

        Model::Role getRole() const;
        void setRole(const Model::Role &value);

    private:
        int idAccesRule;
        Model::Module module;
        Model::Role role;
        Model::DetailsModule detailModule;
        bool access;
    };
}

#endif // ACCESSRULE_H
