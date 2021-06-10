#ifndef TYPEPARAMETREGLOBAL_H
#define TYPEPARAMETREGLOBAL_H

#include <QString>
#include <QUrlQuery>
#include "comboboxmodel.h"

namespace Model {
class TypeParametreGlobal:public ComboBoxModel
{
public:
    TypeParametreGlobal();

    QUrlQuery toUrlQuery() const;

    int getIdType() const;
    void setIdType(int value);

    QString getCode() const;
    void setCode(const QString &value);

    QString getLibelle() const;
    void setLibelle(const QString &value);

    int getId() const override;
    QString getLabel() const override;

private:
    int idType;
    QString code;
    QString libelle;
};
}
#endif // TYPEPARAMETREGLOBAL_H
