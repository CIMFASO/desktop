#ifndef SESSION_H
#define SESSION_H

#include <QObject>
#include "models/user.h"

namespace Model {
    class Session
    {
    public:
        Session();

        int getIdSession() const;
        void setIdSession(int value);

        QString getDebut() const;
        void setDebut(const QString &value);

        QString getFin() const;
        void setFin(const QString &value);

        Model::User getUser() const;
        void setUser(const Model::User &value);

        QUrlQuery toUrlQuery() const;

    private:
        int idSession;
        QString debut;
        QString fin;
        Model::User user;
    };
}

#endif // SESSION_H
