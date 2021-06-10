#include "user.h"

namespace Model {
    User::User()
    {

    }

    int User::getIdUser() const
    {
        return idUser;
    }

    void User::setIdUser(int value)
    {
        idUser = value;
    }

    bool User::getStatut() const
    {
        return statut;
    }

    void User::setStatut(bool value)
    {
        statut = value;
    }

    QString User::getLogin() const
    {
        return login;
    }

    void User::setLogin(const QString &value)
    {
        login = value;
    }

    QString User::getPassword() const
    {
        return password;
    }

    void User::setPassword(const QString &value)
    {
        password = value;
    }
    
    QString User::getNom() const
    {
        return nom;
    }
    
    void User::setNom(const QString &value)
    {
        nom = value;
    }
    
    QString User::getPrenom() const
    {
        return prenom;
    }
    
    void User::setPrenom(const QString &value)
    {
        prenom = value;
    }
    
    QString User::getTelephone() const
    {
        return telephone;
    }
    
    void User::setTelephone(const QString &value)
    {
        telephone = value;
    }
    QUrlQuery User::toUrlQuery() const
    {
        QUrlQuery query;
        query.addQueryItem("iduser",QString::number(idUser));
        query.addQueryItem("nom",nom);
        query.addQueryItem("prenom",prenom);
        query.addQueryItem("telephone",telephone);
        query.addQueryItem("login",login);
        query.addQueryItem("password",password);
        query.addQueryItem("email",email);
        query.addQueryItem("statut",QString::number(statut));

        return query;

    }

    QString User::getLabel() const
    {
        return nom + " " + prenom;
    }

    int User::getId() const
    {
        return idUser;
    }
    
    QString User::getEmail() const
    {
        return email;
    }
    
    void User::setEmail(const QString &value)
    {
        email = value;
    }
}
