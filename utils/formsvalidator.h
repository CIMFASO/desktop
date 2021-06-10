#ifndef FORMSVALIDATOR_H
#define FORMSVALIDATOR_H

#include <QObject>
#include <QRegExp>
#include <QLineEdit>
#include <QIntValidator>
#include <QDoubleValidator>
#include <QRegExpValidator>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionValidator>

class FormsValidator : public QObject
{
    Q_OBJECT
public:
    FormsValidator();
    enum ValidatorType {CODEPATIENT,
                        EMAIL,
                        PHONE,
                        FAX,
                        CNIB,
                        PASSPORT,
                        PRENOMS,
                        NOM,
                        AGE,
                        FILE,
                        URL,
                        TEXT,
                        ALPHA,
                        CODE_6,
                        CODE_5,
                        CODE_4,
                        CODE_PRODUIT,
                        CODE_EXAMEN,
                        CODE_GROUPE,
                        LIBELLE_30,
                        LIBELLE_40,
                        LIBELLE_50,
                        LIBELLE_100,
                        CUSTOM};
    static bool validate(QLineEdit *widget, ValidatorType type, QString regExp = QString(), int minLength = 0, int maxLength = 0);
    static bool validate();
    static void showErrors();
    static void registerWidget(QLineEdit *lineEdit,ValidatorType type);
    static void registerWidget(QLineEdit *lineEdit, QDoubleValidator *dv);
    static void registerWidget(QLineEdit *lineEdit,QIntValidator *iv);
    static void clear();
private:
    static QMap<QLineEdit*,QString> widgets;
    static QList<QLineEdit*> validatedWidgets;
    static QMap<QLineEdit*,ValidatorType> registeredWidgets;
    static QMap<QLineEdit*,QDoubleValidator*> doubleRegisteredWidgets;
    static QMap<QLineEdit*,QIntValidator*> intRegisteredWidgets;
};

#endif // FORMSVALIDATOR_H
