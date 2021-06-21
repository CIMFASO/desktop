#include "modulemanager.h"

namespace Model {
    ModuleManager::ModuleManager()
    {
        listModule.append(new Module(Modules::ListeBL,"LISTE BL"));
        listModule.append(new Module(Modules::Factures,"FACTURES"));
        listModule.append(new Module(Modules::EtatsFactures,"ETATS FACTURES"));
        listModule.append(new Module(Modules::Parametrage,"PARAMETRAGE"));
        listModule.append(new Module(Modules::Securite,"SECURITE"));

        listDetailModule.append(new DetailsModule(ListeBLAfficherListe,getModuleById(Modules::ListeBL),"Afficher liste des BL"));

        listDetailModule.append(new DetailsModule(FacturesAfficherListe,getModuleById(Modules::Factures),"Afficher factures"));

        listDetailModule.append(new DetailsModule(EtatsFacturesAfficher,getModuleById(Modules::EtatsFactures),"Liste des états factures"));
        listDetailModule.append(new DetailsModule(EtatsFacturesAnnulerFacture,getModuleById(Modules::EtatsFactures),"Annuler factures controlées"));

        listDetailModule.append(new DetailsModule(ParametrageTransporteur,getModuleById(Modules::Parametrage),"Transporteurs"));
        listDetailModule.append(new DetailsModule(ParametrageDestination,getModuleById(Modules::Parametrage),"Destinations"));
        listDetailModule.append(new DetailsModule(ParametrageTaxes,getModuleById(Modules::Parametrage),"Taxes"));
        listDetailModule.append(new DetailsModule(ParametrageGroupesUtilisateurs,getModuleById(Modules::Parametrage),"Groupes utilisateurs"));

        //Securité
        listDetailModule.append(new DetailsModule(SecuriteUtilisateurs,getModuleById(Modules::Securite),"Utilisateurs"));
        listDetailModule.append(new DetailsModule(SecuriteGroupesUtilisateurs,getModuleById(Modules::Securite),"Roles des utilisateurs"));
        listDetailModule.append(new DetailsModule(SecuriteDroitsAccess,getModuleById(Modules::Securite),"Droits d'accès"));

    }

    Module *ModuleManager::getModuleById(const int &id)
    {
        for(Module* m : listModule){
            if(m->getIdModule() == id){
                return m;
            }
        }
        return new Module();
    }

    DetailsModule *ModuleManager::getDetailModuleById(const int &id)
    {
        for(DetailsModule* m : listDetailModule){
            if(m->getIdDetail() == id){
                return m;
            }
        }
        return new DetailsModule();
    }

    Module *ModuleManager::getModuleByName(const QString &name)
    {
        for(Module* m : listModule){
            if(m->getIntitule() == name){
                return m;
            }
        }
        return new Module();
    }

    DetailsModule *ModuleManager::getDetailModuleByName(const QString &name)
    {
        for(DetailsModule* m : listDetailModule){
            if(m->getIntitule() == name){
                return m;
            }
        }
        return new DetailsModule();
    }

    QList<Module *> ModuleManager::getListModule() const
    {
        return listModule;
    }

    void ModuleManager::setListModule(const QList<Module *> &value)
    {
        listModule = value;
    }

    QList<DetailsModule *> ModuleManager::getListDetailModule() const
    {
        return listDetailModule;
    }

    void ModuleManager::setListDetailModule(const QList<DetailsModule *> &value)
    {
        listDetailModule = value;
    }
}
