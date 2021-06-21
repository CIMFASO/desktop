#ifndef TAXE_H
#define TAXE_H

#include <QUrlQuery>

namespace Model {
class Taxe{
public:
    Taxe();

    int getIdTaxe() const;
    void setIdTaxe(int value);

    QString getLibelle() const;
    void setLibelle(const QString &value);

    double getTaux() const;
    void setTaux(double value);

    QUrlQuery toUrlQuery() const;
private:
    int idTaxe;
    QString libelle;
    double taux;
};
}

#endif //TAXE_H
