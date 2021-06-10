#ifndef DETAILSMODULE_H
#define DETAILSMODULE_H

#include <QUrlQuery>
#include "models/module.h"

namespace Model {
    class DetailsModule
    {
    public:
        DetailsModule();

        DetailsModule(Module *module,QString name);
        DetailsModule(int id,Module *module,QString name);

        int getIdDetail() const;
        void setIdDetail(int value);

        QString getIntitule() const;
        void setIntitule(const QString &value);

        Module *getModule() const;
        void setModule(Module *value);

    private:
        int idDetail;
        Module *module;
        QString intitule;
    };
}

#endif // DETAILSMODULE_H
