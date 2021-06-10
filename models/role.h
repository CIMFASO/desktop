#ifndef ROLES_H
#define ROLES_H

#include "models/comboboxmodel.h"
#include <QUrlQuery>
#include <QString>

namespace Model {
class Role
{
public:
    Role();

    int getIdRole() const;
    void setIdRole(int value);

    QString getLibelle() const;
    void setLibelle(const QString &value);

    bool getStatut() const;
    void setStatut(bool value);

    QString getCode() const;
    void setCode(const QString &value);

    QUrlQuery toUrlQuery() const;

private:
    int idRole;
    QString code;
    QString libelle;
    bool statut;
};
}
#endif // ROLES_H
