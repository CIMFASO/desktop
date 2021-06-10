#include "formsvalidator.h"
#include <QToolTip>
#include <QStyle>

QMap<QLineEdit*,QString> FormsValidator::widgets;
QList<QLineEdit*> FormsValidator::validatedWidgets;
QMap<QLineEdit*,FormsValidator::ValidatorType> FormsValidator::registeredWidgets;
QMap<QLineEdit*,QDoubleValidator*> FormsValidator::doubleRegisteredWidgets;
QMap<QLineEdit*,QIntValidator*> FormsValidator::intRegisteredWidgets;

FormsValidator::FormsValidator()
{

}

bool FormsValidator::validate(QLineEdit *widget,ValidatorType type,const QString regExpPattern,int minLength,int maxLength)
{
    QString content = widget->text().trimmed();
    int pos = 0;
    QRegularExpression rx;
    QString retValue;
    if(type == ValidatorType::NOM){
        rx.setPattern("^[\\w\\W]{2,30}$");
        retValue = "Seules 2 à 30 caractères sont autorisés";
    }
    else if(type == ValidatorType::PRENOMS){
        rx.setPattern("^[\\w\\W]{2,70}$");
        retValue = "Seules 2 à 70 caractères sont autorisés";
    }else if(type == ValidatorType::PHONE){
        rx.setPattern("^\\d{15,15}$");
        retValue = "8 chiffres obligatoires";
    }
    else if(type == ValidatorType::CODE_5){
        rx.setPattern("^[A-Z]{1}\\d{4,4}$");
        retValue = "Le code doit contenir une lettre majuscule suivit de 4 chiffres";
    }
    else if(type == ValidatorType::CODE_4){
        rx.setPattern("^[A-Z]{1}\\d{3,3}$");
        retValue = "Le code doit contenir une lettre majuscule suivit de 3 chiffres";
    }
    else if(type == ValidatorType::CODE_6){
        rx.setPattern("^[1-9]{1}[0-9]{0,5}$");
        retValue = "Le code doit avoir 1 à 6 chiffres.";
    }
    else if(type == ValidatorType::CODE_EXAMEN){
        rx.setPattern("^[E]\\d{4,4}$");
        retValue = "Le code doit contenir la lettre E suivit de 4 chiffres";
    }
    else if(type == ValidatorType::CODEPATIENT){
        rx.setPattern("^[P]\\d{7,7}$");
        retValue = "Le code doit contenir la lettre P suivit de 7 chiffres";
    }
    else if (type==ValidatorType::CODE_PRODUIT) {
        rx.setPattern("^[PRO]\\d{5,5}$");
        retValue = "Le code doit contenir les lettres PRO suivit de 5 chiffres";
    }else if (type==ValidatorType::CODE_GROUPE) {
        rx.setPattern("^[G]\\d{4,7}$");
        retValue = "Le code doit contenir les lettres G suivit de 4 chiffres";
    }else if(type == ValidatorType::EMAIL){
        rx.setPattern("\\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,4}\\b");
        retValue = "Erreur: seuls les caractères alphanumériques et ., _ , @ , - sont autorisés";
    }else if(type == ValidatorType::LIBELLE_30){
        rx.setPattern("^[\\w\\W]{2,30}$");
        retValue = "Seules 2 à 30 caractères alphabétiques sont autorisés";
    }
    else if(type == ValidatorType::LIBELLE_40){
        rx.setPattern("^[\\w\\W]{2,40}$");
        retValue = "Seules 2 à 40 caractères alphabétiques sont autorisés";
    }
    else if(type == ValidatorType::LIBELLE_50){
        rx.setPattern("^[\\w\\W]{2,50}$");
        retValue = "Seules 2 à 50 caractères alphabétiques sont autorisés";
    }else if(type == ValidatorType::LIBELLE_100){
        rx.setPattern("^[\\w\\W]{2,100}$");
        retValue = "Seules 2 à 100 caractères alphabétiques sont autorisés";
    }
    else if(type == ValidatorType::CUSTOM){
        rx.setPattern(regExpPattern);
        retValue = "Invalide";
    }

    widgets.insert(widget,retValue);

    QValidator *rv = new QRegularExpressionValidator(rx);
    QValidator::State v = rv->validate(content,pos);
    if(v == QValidator::Acceptable){
        validatedWidgets.append(widget);
        return true;
    }else
        return false;
    rv->deleteLater();
}

bool FormsValidator::validate()
{
    validatedWidgets.clear();
    QList<bool> results;
    QMapIterator<QLineEdit*,ValidatorType> i(registeredWidgets);
    while (i.hasNext()) {
        i.next();
        results.append(validate(i.key(),i.value()));
    }

    QMapIterator<QLineEdit*,QDoubleValidator*> id(doubleRegisteredWidgets);
    while (id.hasNext()) {
        id.next();
        id.value()->setLocale(QLocale::English);
        widgets.insert(id.key(),"Entrer un nombre(entier ou décimal) compris entre " + QString::number(id.value()->bottom()) + " et " + QString::number(id.value()->top(),'g',10));
        QString content = id.key()->text().trimmed();
        int pos = 0;
        bool valid = id.value()->validate(content,pos) == QDoubleValidator::Acceptable ? true : false;
        if(valid) validatedWidgets.append(id.key());
        results.append(valid);
    }

    QMapIterator<QLineEdit*,QIntValidator*> iv(intRegisteredWidgets);
    while (iv.hasNext()) {
        iv.next();
        widgets.insert(iv.key(),"Entrer un entier compris entre " + QString::number(iv.value()->bottom()) + " et " + QString::number(iv.value()->top(),'g',10));
        QString content = iv.key()->text().trimmed();
        int pos = 0;
        bool valid = iv.value()->validate(content,pos) == QIntValidator::Acceptable ? true : false;
        if(valid) validatedWidgets.append(iv.key());
        results.append(valid);
    }

    return !results.contains(false);
}

void FormsValidator::showErrors()
{
    QMapIterator<QLineEdit*,QString> i(widgets);
    while (i.hasNext()) {
        i.next();
        if(!validatedWidgets.contains(i.key())){
            //i.key()->clear();
            i.key()->setStyleSheet("QToolTip{background-color:red;color:white;border: 1px solid red;padding:5px;font-size: 12px;}\n"
                                   "QLineEdit{color: black;border: 2px solid red;}\n"
                                   "QLineEdit[text=\"\"]{font-size: 11px;border: 2px solid red;color: red;}");
            i.key()->setToolTip(i.value());
            //QToolTip::showText(i.key()->mapToGlobal(QPoint(0,0)),i.value());
            i.key()->setPlaceholderText(i.value());

            connect(i.key(),&QLineEdit::textChanged,[=]{
                i.key()->style()->polish(i.key());
                i.key()->setPlaceholderText("");
                i.key()->setStyleSheet("");
                i.key()->setToolTip("");
            });
        }/*else{
            i.key()->setStyleSheet("QToolTip{background-color:green;color:white;border: 1px solid green;padding:5px;font-size: 12px;}\n"
                                   "QLineEdit{color: black;border: 2px solid green;}\n");
            i.key()->setToolTip("Contenu valide");
            connect(i.key(),&QLineEdit::textChanged,[=]{
                i.key()->style()->polish(i.key());
                i.key()->setStyleSheet("");
                i.key()->setToolTip("");
            });
        }*/
    }
    widgets.clear();
    registeredWidgets.clear();
    doubleRegisteredWidgets.clear();
    intRegisteredWidgets.clear();
}
void FormsValidator::registerWidget(QLineEdit *lineEdit,ValidatorType type)
{
    if(!registeredWidgets.contains(lineEdit))
        registeredWidgets.insert(lineEdit,type);
}

void FormsValidator::registerWidget(QLineEdit *lineEdit,QDoubleValidator *dv)
{
    if(!doubleRegisteredWidgets.contains(lineEdit))
        doubleRegisteredWidgets.insert(lineEdit,dv);
}

void FormsValidator::registerWidget(QLineEdit *lineEdit,QIntValidator *iv)
{
    if(!intRegisteredWidgets.contains(lineEdit))
        intRegisteredWidgets.insert(lineEdit,iv);
}

void FormsValidator::clear()
{
    intRegisteredWidgets.clear();
    doubleRegisteredWidgets.clear();
    registeredWidgets.clear();
    validatedWidgets.clear();
    widgets.clear();
}
