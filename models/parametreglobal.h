#ifndef PARAMETREGLOBAL_H
#define PARAMETREGLOBAL_H

#include <QString>
#include <QUrlQuery>
#include "comboboxmodel.h"
#include "models/typeparametreglobal.h"

namespace Model {
class ParametreGlobal : public ComboBoxModel
{
public:
    ParametreGlobal();

    int getIdParam() const;
    void setIdParam(int value);

    QString getCode() const;
    void setCode(const QString &value);

    Model::TypeParametreGlobal getTypeParametre() const;
    void setTypeParametre(const Model::TypeParametreGlobal &value);

    QString getLibelle() const;
    void setLibelle(const QString &value);

    QUrlQuery toUrlQuery() const;

    QString getLabel() const override;
    int getId() const override;
private:
    int idParam;
    QString code;
    Model::TypeParametreGlobal typeParametre;
    QString libelle;
};
}
#endif // PARAMETREGLOBAL_H
