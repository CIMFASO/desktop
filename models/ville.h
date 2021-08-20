#ifndef VILLE_H
#define VILLE_H

#include <QUrlQuery>

namespace Model {
class Ville
{
public:
    Ville();

    int getId() const;
    void setId(int newId);

    const QString &getNom() const;
    void setNom(const QString &newNom);

    QUrlQuery toUrlQuery() const;

private:
    int id;
    QString nom;
};
}
#endif // VILLE_H
