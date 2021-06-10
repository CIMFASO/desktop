#ifndef TRANSPORTEUR_H
#define TRANSPORTEUR_H

#include <QUrlQuery>
#include "models/comboboxmodel.h"

namespace Model {
class Transporteur : public ComboBoxModel
{
public:
    Transporteur();

    QUrlQuery toUrlQuery() const;
    int getId() const override;

    QString getNom() const;
    void setNom(const QString &value);

    QString getCode() const;
    void setCode(const QString &value);

    QString getTelephone() const;
    void setTelephone(const QString &value);

    QString getLabel() const override;

    int getIdTransp() const;
    void setIdTransp(int value);

    QString getType() const;
    void setType(const QString &value);

    bool getTva() const;
    void setTva(bool value);

    bool getBic() const;
    void setBic(bool value);

    bool getRetNat() const;
    void setRetNat(bool value);

    bool getRetInt() const;
    void setRetInt(bool value);

private:
    int idTransp;
    QString nom;
    QString code;
    QString type;
    QString telephone;
    bool tva;
    bool bic;
    bool retNat;
    bool retInt;
};
}
#endif // TRANSPORTEUR_H
