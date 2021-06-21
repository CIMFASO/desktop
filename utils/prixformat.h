#ifndef PRIXFORMAT_H
#define PRIXFORMAT_H

#include <QString>
#include <QStringList>

class PrixFormat
{
public:
    PrixFormat();
    //cette fonction permet de formater les prix en ajoutant un espace à chaque
    //position de 3 chiffres afin de rendre les prix plus lisibles
    // EX: 145000 ==> 145 000
    static QString format(const int &prix)
    {
        QString m = QString::number(prix);
        QString temp_formated,formated;
        int len = m.size();
        int dot = 0;

        for (int i = 0; i < len; i++) {
            temp_formated += m[len-i-1];
            int s = temp_formated.size()-dot;
            //on ajoute un espace à chaque trois chiffres
            if(s%3 == 0 && len != s){
                temp_formated += " ";
                dot++;
            }
        }
        int temp_len = temp_formated.size();
        for (int i = 0; i < temp_len; i++) {
            formated += temp_formated[temp_len-i-1];
        }
        return formated;
    }

    static QString format(QString prix)
    {
        QStringList list;
        QString m;
        if(prix.contains(".")){
            list = prix.split(".");
            m = list.at(0);
        }else{
            m = prix;
        }

        QString temp_formated,formated;
        int len = m.size();
        int dot = 0;

        for (int i = 0; i < len; i++) {
            temp_formated += m[len-i-1];
            int s = temp_formated.size()-dot;
            //on ajoute un espace à chaque trois chiffres
            if(s%3 == 0 && len != s){
                temp_formated += " ";
                dot++;
            }
        }
        int temp_len = temp_formated.size();
        for (int i = 0; i < temp_len; i++) {
            formated += temp_formated[temp_len-i-1];
        }

        return prix.contains(".") ? formated + "." + list.at(1) : formated;
    }

    static QString format(double p)
    {
        QStringList list;
        QString m,prix = QString::number(p,'g',10);
        if(prix.contains(".")){
            list = prix.split(".");
            m = list.at(0);
        }else{
            m = prix;
        }

        QString temp_formated,formated;
        int len = m.size();
        int dot = 0;

        for (int i = 0; i < len; i++) {
            temp_formated += m[len-i-1];
            int s = temp_formated.size()-dot;
            //on ajoute un espace à chaque trois chiffres
            if(s%3 == 0 && len != s){
                temp_formated += " ";
                dot++;
            }
        }
        int temp_len = temp_formated.size();
        for (int i = 0; i < temp_len; i++) {
            formated += temp_formated[temp_len-i-1];
        }

        return prix.contains(".") ? formated + "." + list.at(1) : formated;
    }

    static QString formatt(QString montant)
    {
        QString m = "",temp;
        while(montant.length() > 3){
            temp = m;
            m = " ";
            m += montant.right(3);
            m = temp + m;
            montant = montant.left(montant.length()-3);
        }
        return m;
    }
};

#endif // PRIXFORMAT_H
