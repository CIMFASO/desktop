#ifndef MODULEMANAGER_H
#define MODULEMANAGER_H

#include "models/module.h"
#include "models/detailsmodule.h"
#include <QList>

namespace Model {


class ModuleManager
{
public:
    ModuleManager();
    ~ModuleManager(){
        for(Module *m : listModule){
            delete m;
        }

        for(DetailsModule *d : listDetailModule){
            delete d;
        }
    };
    Module *getModuleById(const int &id);
    DetailsModule *getDetailModuleById(const int &id);
    Module *getModuleByName(const QString &name);
    DetailsModule *getDetailModuleByName(const QString &name);

    QList<Module *> getListModule() const;
    void setListModule(const QList<Module *> &value);

    QList<DetailsModule *> getListDetailModule() const;
    void setListDetailModule(const QList<DetailsModule *> &value);

    enum Modules{
        ListeBL = 1,
        Factures,
        Parametrage,
        Securite,
        EtatsFactures,
    };
    enum ListeBL{
        ListeBLAfficherListe = 101
    };

    enum Factures{
        FacturesAfficherListe = 201
    };

    enum Parametrage{
        ParametrageTransporteur = 301,
        ParametrageDestination,
        ParametrageTaxes,
        ParametrageGroupesUtilisateurs
    };
    enum Securite{
        SecuriteUtilisateurs = 401,
        SecuriteGroupesUtilisateurs,
        SecuriteDroitsAccess
    };

    enum EtatsFactures{
        EtatsFacturesAfficher = 501,
        EtatsFacturesAnnulerFacture
    };

private:
    QList <Module*> listModule;
    QList <DetailsModule*> listDetailModule;
};
}
#endif // MODULEMANAGER_H
