#include "module.h"
namespace Model {

    Module::Module()
    {

    }

    Module::Module(int id, QString name)
    {
        this->idModule = id;
        this->intitule = name;
    }

    Module::Module(QString name)
    {
        this->intitule = name;
    }

    QString Module::getIntitule() const
    {
        return intitule;
    }

    void Module::setIntitule(const QString &value)
    {
        intitule = value;
    }

    int Module::getIdModule() const
    {
        return idModule;
    }

    void Module::setIdModule(int value)
    {
        idModule = value;
    }
}
