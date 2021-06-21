#ifndef UTILS_H
#define UTILS_H

#include <QSettings>
#include <QString>
#include <QDateTime>

class Utils
{

public:
    Utils();
    static QString server(){
        QSettings settings;
        return "http://"+
                settings.value("host").toString()+
                ":"+
                settings.value("port").toString()+
                "/app_gestion/";
    };

    static QString logFilePath(){
        QSettings settings;
        return settings.value("logFilePath").toString();
    }

    static QString host(){
        QSettings settings;
        return settings.value("host").toString();
    };

    static int port(){
        QSettings settings;
        return settings.value("port").toInt();
    };

    static int currentUserId(){
        QSettings settings;
        settings.beginGroup("LOGIN");
        int id = settings.value("iduser").toInt();
        settings.endGroup();
        return id;
    };

    static int currentUserRoleId(){
        QSettings settings;
        settings.beginGroup("LOGIN");
        int id = settings.value("idrole").toInt();
        settings.endGroup();
        return id;
    };

    static QString currentUserRoleCode(){
        QSettings settings;
        settings.beginGroup("LOGIN");
        QString str = settings.value("rolecode").toString();
        settings.endGroup();
        return str;
    };

    static QString currentUserLogin(){
        QSettings settings;
        settings.beginGroup("LOGIN");
        QString login = settings.value("login").toString();
        settings.endGroup();
        return login;
    };

    static QString currentUserNom(){
        QSettings settings;
        settings.beginGroup("LOGIN");
        QString login = settings.value("nom").toString();
        settings.endGroup();
        return login;
    };

    static QString currentUserPrenom(){
        QSettings settings;
        settings.beginGroup("LOGIN");
        QString login = settings.value("prenom").toString();
        settings.endGroup();
        return login;
    };

    static int currentSessionId(){
        QSettings settings;
        settings.beginGroup("SESSIONS");
        int id = settings.value("idsession").toInt();
        settings.endGroup();
        return id;
    };

    static int currentSessionUserId(){
        QSettings settings;
        settings.beginGroup("SESSIONS");
        int id = settings.value("siduser").toInt();
        settings.endGroup();
        return id;
    };
    static QString openedSessionUserLogin(){
        QSettings settings;
        settings.beginGroup("SESSIONS");
        QString str = settings.value("slogin").toString();
        settings.endGroup();
        return str;
    };

    static bool isSessionOpened(){
        QSettings settings;
        settings.beginGroup("SESSIONS");
        bool etat = settings.value("etat").toBool();
        settings.endGroup();
        return etat;
    }

    static double TVA(){
        QSettings settings;
        settings.beginGroup("TAXES");
        double v = settings.value("TVA").toDouble();
        settings.endGroup();
        return v;
    }

    static double BIC(){
        QSettings settings;
        settings.beginGroup("TAXES");
        double v = settings.value("BIC").toDouble();
        settings.endGroup();
        return v;
    }

    static double RETN(){
        QSettings settings;
        settings.beginGroup("TAXES");
        double v = settings.value("RET_N").toDouble();
        settings.endGroup();
        return v;
    }
    static double RETI(){
        QSettings settings;
        settings.beginGroup("TAXES");
        double v = settings.value("RET_I").toDouble();
        settings.endGroup();
        return v;
    }
    static QString dateFormat(const QString &date,const QString &from = "yyyy-MM-dd",const QString &to = "dd/MM/yyyy"){
        return QDate::fromString(date,from).toString(to);
    }
    static QString dateFormat(const QDate &date,const QString &format= "dd/MM/yyyy"){
        return date.toString(format);
    }
    static QString dateTimeFormat(const QString &date,const QString &from = "yyyy-MM-dd hh:mm:ss",const QString &to="dd/MM/yyyy  hh:mm"){
        return QDateTime::fromString(date,from).toString(to);
    }
    static QString dateTimeFormat(const QDateTime &dateTime,const QString &format="dd/MM/yyyy  hh:mm"){
        return dateTime.toString(format);
    }

    enum TypeParameGlobal{
        TypeDocuments = 01,
    };
};

#endif // UTILS_H
