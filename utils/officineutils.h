#ifndef OFFICINEUTILS_H
#define OFFICINEUTILS_H

#include <QSettings>
#include <QString>

class Officine{
public:
    Officine();

    static int IdOfficine(){

    }
    static QString RaisonSociale(){
        QSettings settings;
        settings.beginGroup("OFFICINE");
        QString login = settings.value("raisonsociale").toString();
        settings.endGroup();
        return login;
    }
    static QString Responsable(){
        QSettings settings;
        settings.beginGroup("OFFICINE");
        QString login = settings.value("responsable").toString();
        settings.endGroup();
        return login;
    }
    static QString NumeroCNSS(){
        QSettings settings;
        settings.beginGroup("OFFICINE");
        QString login = settings.value("cnss").toString();
        settings.endGroup();
        return login;
    }
    static QString NumeroIFU(){
        QSettings settings;
        settings.beginGroup("OFFICINE");
        QString login = settings.value("ifu").toString();
        settings.endGroup();
        return login;
    }
    static QString NumeroRCCM(){
        QSettings settings;
        settings.beginGroup("OFFICINE");
        QString login = settings.value("rccm").toString();
        settings.endGroup();
        return login;
    }
    static QString NumeroCompte(){
        QSettings settings;
        settings.beginGroup("OFFICINE");
        QString login = settings.value("compte").toString();
        settings.endGroup();
        return login;
    }
    static QString AdressePostale(){
        QSettings settings;
        settings.beginGroup("OFFICINE");
        QString login = settings.value("adressepostale").toString();
        settings.endGroup();
        return login;
    }
    static QString Localisation(){
        QSettings settings;
        settings.beginGroup("OFFICINE");
        QString login = settings.value("localisation").toString();
        settings.endGroup();
        return login;
    }
    static QString RegimeFiscal(){
        QSettings settings;
        settings.beginGroup("OFFICINE");
        QString login = settings.value("regimefiscal").toString();
        settings.endGroup();
        return login;
    }
    static QString DivisionFiscale(){
        QSettings settings;
        settings.beginGroup("OFFICINE");
        QString login = settings.value("divisionfiscal").toString();
        settings.endGroup();
        return login;
    }
    static QString Tel1(){
        QSettings settings;
        settings.beginGroup("OFFICINE");
        QString login = settings.value("tel1").toString();
        settings.endGroup();
        return login;
    }
    static QString Tel2(){
        QSettings settings;
        settings.beginGroup("OFFICINE");
        QString login = settings.value("tel2").toString();
        settings.endGroup();
        return login;
    }
    static QString Email(){
        QSettings settings;
        settings.beginGroup("OFFICINE");
        QString login = settings.value("email").toString();
        settings.endGroup();
        return login;
    }
    static QString Signature(){
        QSettings settings;
        settings.beginGroup("OFFICINE");
        QString login = settings.value("signature").toString();
        settings.endGroup();
        return login;
    }
};

#endif // OFFICINEUTILS_H
