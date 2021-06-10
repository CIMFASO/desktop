#ifndef LETTERSCONVERSIONUTILS_H
#define LETTERSCONVERSIONUTILS_H

#include <QString>
#include <QDebug>
#include "math.h"

class LettersConversionUtils
{
public:
    LettersConversionUtils();

public:
    static const long long MILLIARD  = 1000000000;
    static const long  MILLION   = 1000000;
    static const int MILLIER   = 1000;
    static const int CENTAINE  = 100;
    static const int DIZAINE   = 10;
    static const int UNITE     = 1;

    static QString convert(long long nombre)
    {
        int unite,dizaine,centaine,millier,million,milliard;
        QString lettre {""};

        milliard = std::floor(nombre/MILLIARD);
        million  = std::floor((nombre - (milliard*MILLIARD))/MILLION);
        millier  = std::floor((nombre - (milliard*MILLIARD) - (million*MILLION))/MILLIER);
        centaine = std::floor((nombre - (milliard*MILLIARD) - (million*MILLION) - (millier*MILLIER))/CENTAINE);
        dizaine  = std::floor((nombre - (milliard*MILLIARD) - (million*MILLION) - (millier*MILLIER) - (centaine*CENTAINE)) / DIZAINE);
        unite    = std::floor((nombre - (milliard*MILLIARD) - (million*MILLION) - (millier*MILLIER) - (centaine*CENTAINE) - (dizaine*DIZAINE)) / UNITE);

        lettre += centaines(milliard);
        milliard > 0 ? lettre += "MILLIARD " : lettre += " ";

        lettre += centaines(million);

        million > 0 ? lettre += "MILLION " : lettre += " ";


        lettre += centaines(millier);
        millier > 0 ? lettre += "MILLE " : lettre += " ";

        //la part des centaines
        int cent = (centaine*CENTAINE)+(dizaine*DIZAINE) + unite;

        lettre += centaines(cent);

        return lettre.trimmed();
    }

    static QString centaines(long nombre){
        int unite,dizaine,centaine;
        QString lettre {""};
        centaine = std::floor((nombre) / CENTAINE);
        dizaine  = std::floor((nombre - (centaine*CENTAINE)) / DIZAINE);
        unite    = std::floor((nombre - (centaine*CENTAINE) - (dizaine*DIZAINE)) / UNITE);

        switch (centaine) {
        case 1:
            lettre += "CENT ";
        break;
        case 2:
            lettre += "DEUX CENT ";
        break;
        case 3:
            lettre += "TROIS CENT ";
        break;
        case 4:
            lettre += "QUATRE CENT ";
        break;
        case 5:
            lettre += "CINQ CENT ";
        break;
        case 6:
            lettre += "SIX CENT ";
        break;
        case 7:
            lettre += "SEPT CENT ";
        break;
        case 8:
            lettre += "HUIT CENT ";
        break;
        case 9:
            lettre += "NEUF CENT ";
        break;
        case 0:
            lettre += " ";
        break;
        }

        //la part des unités et dizaines
        int diz = (dizaine*DIZAINE) + (unite*UNITE);

        switch (diz) {
        case 1:
            lettre += "UN ";
            break;
        case 2:
            lettre += "DEUX ";
            break;
        case 3:
            lettre += "TROIS ";
            break;
        case 4:
            lettre += "QUATRE ";
            break;
        case 5:
            lettre += "CINQ ";
            break;
        case 6:
            lettre += "SIX ";
            break;
        case 7:
            lettre += "SEPT ";
            break;
        case 8:
            lettre += "HUIT ";
            break;
        case 9:
            lettre += "NEUF ";
            break;
        case 10:
            lettre += "DIX ";
        break;
        case 11:
            lettre += "ONZE ";
        break;
        case 12:
            lettre += "DOUZE ";
        break;
        case 13:
            lettre += "TREIZE ";
        break;
        case 14:
            lettre += "QUATORZE ";
        break;
        case 15:
            lettre += "QUINZE ";
        break;
        case 16:
            lettre += "SEIZE ";
        break;
        case 17:
            lettre += "DIX SEPT ";
        break;
        case 18:
            lettre += "DIX HUIT ";
        break;
        case 19:
            lettre += "DIX NEUF ";
        break;
        case 20:
            lettre += "VINGT ";
        break;
        case 21:
            lettre += "VINGT UN";
        break;
        case 22:
            lettre += "VINGT DEUX ";
        break;
        case 23:
            lettre += "VINGT TROIS ";
        break;
        case 24:
            lettre += "VINGT QUATRE ";
        break;
        case 25:
            lettre += "VINGT CINQ ";
        break;
        case 26:
            lettre += "VINGT SIX ";
        break;
        case 27:
            lettre += "VINGT SEPT ";
        break;
        case 28:
            lettre += "VINGT HUIT ";
        break;
        case 29:
            lettre += "VINGT NEUF ";
        break;
        case 30:
            lettre += "TRENTE ";
        break;
        case 31:
            lettre += "TRENTE UN ";
        break;
        case 32:
            lettre += "TRENTE DEUX ";
        break;
        case 33:
            lettre += "TRENTE TROIS ";
        break;
        case 34:
            lettre += "TRENTE QUATRE ";
        break;
        case 35:
            lettre += "TRENTE CINQ ";
        break;
        case 36:
            lettre += "TRENTE SIX ";
        break;
        case 37:
            lettre += "TRENTE SEPT ";
        break;
        case 38:
            lettre += "TRENTE HUIT ";
        break;
        case 39:
            lettre += "TRENTE NEUF ";
        break;
        case 40:
            lettre += "QUARANTE ";
        break;
        case 41:
            lettre += "QUARANTE UN ";
        break;
        case 42:
            lettre += "QUARANTE DEUX ";
        break;
        case 43:
            lettre += "QUARANTE TROIS ";
        break;
        case 44:
            lettre += "QUARANTE QUATRE ";
        break;
        case 45:
            lettre += "QUARANTE CINQ ";
        break;
        case 46:
            lettre += "QUARANTE SIX ";
        break;
        case 47:
            lettre += "QUARANTE SEPT ";
        break;
        case 48:
            lettre += "QUARANTE HUIT ";
        break;
        case 49:
            lettre += "QUARANTE NEUF ";
        break;
        case 50:
            lettre += "CINQUANTE ";
        break;
        case 51:
            lettre += "CINQUANTE UN ";
        break;
        case 52:
            lettre += "CINQUANTE DEUX ";
        break;
        case 53:
            lettre += "CINQUANTE TROIS ";
        break;
        case 54:
            lettre += "CINQUANTE QUATRE ";
        break;
        case 55:
            lettre += "CINQUANTE CINQ ";
        break;
        case 56:
            lettre += "CINQUANTE SIX ";
        break;
        case 57:
            lettre += "CINQUANTE SEPT ";
        break;
        case 58:
            lettre += "CINQUANTE HUIT ";
        break;
        case 59:
            lettre += "CINQUANTE NEUF ";
        break;
        case 60:
            lettre += "SOIXANTE ";
        break;
        case 61:
            lettre += "SOIXANTE UN ";
        break;
        case 62:
            lettre += "SOIXANTE DEUX ";
        break;
        case 63:
            lettre += "SOIXANTE TROIS ";
        break;
        case 64:
            lettre += "SOIXANTE QUATRE ";
        break;
        case 65:
            lettre += "SOIXANTE CINQ ";
        break;
        case 66:
            lettre += "SOIXANTE SIX ";
        break;
        case 67:
            lettre += "SOIXANTE SEPT ";
        break;
        case 68:
            lettre += "SOIXANTE HUIT ";
        break;
        case 69:
            lettre += "SOIXANTE NEUF ";
        break;
        case 70:
            lettre += "SOIXANTE DIX ";
        break;
        case 71:
            lettre += "SOIXANTE ONZE ";
        break;
        case 72:
            lettre += "SOIXANTE DOUZE ";
        break;
        case 73:
            lettre += "SOIXANTE TREIZE ";
        break;
        case 74:
            lettre += "SOIXANTE QUATORZE ";
        break;
        case 75:
            lettre += "SOIXANTE QUINZE ";
        break;
        case 76:
            lettre += "SOIXANTE SEIZE ";
        break;
        case 77:
            lettre += "SOIXANTE DIX SEPT ";
        break;
        case 78:
            lettre += "SOIXANTE DIX HUIT ";
        break;
        case 79:
            lettre += "SOIXANTE DIX NEUF ";
        break;
        case 80:
            lettre += "QUATRE VINGT ";
        break;
        case 81:
            lettre += "QUATRE VINGT UN ";
        break;
        case 82:
            lettre += "QUATRE VINGT DEUX ";
        break;
        case 83:
            lettre += "QUATRE VINGT TROIS ";
        break;
        case 84:
            lettre += "QUATRE VINGT QUATRE ";
        break;
        case 85:
            lettre += "QUATRE VINGT CINQ ";
        break;
        case 86:
            lettre += "QUATRE VINGT SIX ";
        break;
        case 87:
            lettre += "QUATRE VINGT SEPT ";
        break;
        case 88:
            lettre += "QUATRE VINGT HUIT ";
        break;
        case 89:
            lettre += "QUATRE VINGT NEUF ";
        break;
        case 90:
            lettre += "QUATRE VINGT DIX ";
        break;
        case 91:
            lettre += "QUATRE VINGT ONZE";
        break;
        case 92:
            lettre += "QUATRE VINGT DOUZE ";
        break;
        case 93:
            lettre += "QUATRE VINGT TREIZE ";
        break;
        case 94:
            lettre += "QUATRE VINGT QUATORZE ";
        break;
        case 95:
            lettre += "QUATRE VINGT QUINZE ";
        break;
        case 96:
            lettre += "QUATRE VINGT SEIZE ";
        break;
        case 97:
            lettre += "QUATRE VINGT DIX SEPT ";
        break;
        case 98:
            lettre += "QUATRE VINGT DIX HUIT ";
        break;
        case 99:
            lettre += "QUATRE VINGT DIX NEUF ";
        break;
        case 0:
            lettre += " ";
        break;
        }

        return  lettre;
    }
};

#endif // LETTERSCONVERSIONUTILS_H
