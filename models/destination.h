#ifndef DESTINATION_H
#define DESTINATION_H

#include <QUrlQuery>
#include "models/comboboxmodel.h"

namespace Model {
class Destination : public ComboBoxModel
{
public:
    Destination();

    int getIdDest() const;
    void setIdDest(int value);

    QString getNom() const;
    void setNom(const QString &value);

    double getTarif() const;
    void setTarif(double value);

    QUrlQuery toUrlQuery() const;

    QString getLabel() const override;
    int getId() const override;
    double getTarifPlat() const;
    void setTarifPlat(double newTarifPlat);

private:
    int idDest;
    QString nom;
    double tarif;
    double tarifPlat;
};
}
#endif // DESTINATION_H
