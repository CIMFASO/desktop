#ifndef MODULE_H
#define MODULE_H
#include <QString>
#include <QUrlQuery>

namespace Model {

    class Module
    {
    public:
        Module();
        Module(int id, QString name);
        Module(QString name);
        QString getIntitule() const;
        void setIntitule(const QString &value);

        int getIdModule() const;
        void setIdModule(int value);
    private:
        int idModule;
        QString intitule;
    };
}
#endif // MODULE_H
