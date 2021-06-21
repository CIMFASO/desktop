#include "messagebox.h"

MessageBox::MessageBox()
{

}

void MessageBox::success(QWidget *parent)
{
    QMessageBox::information(parent,"Success","SUCCES : L'Opération a été effectué avec succès.");
}

void MessageBox::error(QWidget *parent)
{
    QMessageBox::critical(parent,"Erreur","ERREUR : L'Opération a echoué. Veuillez réessayer!");
}

bool MessageBox::warning(QWidget *parent,QString message)
{
    return QMessageBox::question(parent,"Attention",message,QMessageBox::Yes|QMessageBox::No)
            == QMessageBox::Yes ? true : false;
}

bool MessageBox::question(QWidget *parent,QString message)
{
    return QMessageBox::question(parent,"Confirm",message,QMessageBox::Yes|QMessageBox::No)
            == QMessageBox::Yes ? true : false;
}

bool MessageBox::confirmDelete(QWidget *parent, QString message)
{
    return QMessageBox::warning(parent,"Attention",message,QMessageBox::Yes|QMessageBox::No)
            == QMessageBox::Yes ? true : false;
}

bool MessageBox::confirmUpdate(QWidget *parent, QString message)
{
    return QMessageBox::question(parent,"Confirm",message,QMessageBox::Yes|QMessageBox::No)
            == QMessageBox::Yes ? true : false;
}
