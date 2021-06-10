#include "detailsmodule.h"
namespace Model{
    DetailsModule::DetailsModule()
    {

    }

    DetailsModule::DetailsModule(Module *module, QString name)
    {
        this->module = module;
        this->intitule = name;
    }

    DetailsModule::DetailsModule(int id, Module *module, QString name)
    {
        this->idDetail = id;
        this->module = module;
        this->intitule = name;
    }

    int DetailsModule::getIdDetail() const
    {
        return idDetail;
    }

    void DetailsModule::setIdDetail(int value)
    {
        idDetail = value;
    }

    QString DetailsModule::getIntitule() const
    {
        return intitule;
    }

    void DetailsModule::setIntitule(const QString &value)
    {
        intitule = value;
    }

    Module *DetailsModule::getModule() const
    {
        return module;
    }

    void DetailsModule::setModule(Module *value)
    {
        module = value;
    }
}
