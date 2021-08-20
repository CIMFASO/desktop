#ifndef BL_H
#define BL_H

#include <QUrlQuery>

namespace Model {
class BL
{
public:
    BL();

    int getId() const;
    void setId(int value);

    QString getNumBL() const;
    void setNumBL(const QString &value);

    QString getDateBL() const;
    void setDateBL(const QString &value);

    int getProduit() const;
    void setProduit(int value);

    int getQuantite() const;
    void setQuantite(int value);

    QString getNomLocalite() const;
    void setNomLocalite(const QString &value);

    QString getCodeTransp() const;
    void setCodeTransp(const QString &value);

    double getMontantBL() const;
    void setMontantBL(double value);

    QString getStatut() const;
    void setStatut(const QString &value);

    QUrlQuery toUrlQuery() const;

    const QString &getTypeCamion() const;
    void setTypeCamion(const QString &newTypeCamion);

private:
    int id;
    QString numBL;
    QString dateBL;
    int produit;
    int quantite;
    QString typeCamion;
    QString nomLocalite;
    QString codeTransp;
    double montantBL;
    QString statut;
};
}
#endif // BL_H
