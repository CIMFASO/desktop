#ifndef USER_H
#define USER_H

#include <QString>
#include <QUrlQuery>
#include "models/comboboxmodel.h"

namespace Model {
    class User : public ComboBoxModel
    {
    public:
        User();
        int getIdUser() const;
        void setIdUser(int value);

        bool getStatut() const;
        void setStatut(bool value);

        QString getLogin() const;
        void setLogin(const QString &value);

        QString getPassword() const;
        void setPassword(const QString &value);

        QString getNom() const;
        void setNom(const QString &value);

        QString getPrenom() const;
        void setPrenom(const QString &value);

        QString getTelephone() const;
        void setTelephone(const QString &value);

        QUrlQuery toUrlQuery() const;

        QString getLabel() const override;
        int getId() const override;
        QString getEmail() const;
        void setEmail(const QString &value);

    private:
        int idUser;
        bool statut;
        QString login;
        QString email;
        QString password;//crypté
        QString nom, prenom, telephone;
    };
}
#endif // USER_H
