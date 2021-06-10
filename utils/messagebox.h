#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <QMessageBox>

class MessageBox : public QWidget
{
public:
    MessageBox();
    static void success(QWidget *parent=0);
    static void error(QWidget *parent=0);
    static bool warning(QWidget *parent=0,QString message = QString("ATTENTION : Êtes-vous sûr de vouloir continuer ?"));
    static bool question(QWidget *parent=0,QString message = QString("CONFIRM. : Êtes-vous sûr de vouloir continuer ?"));
    static bool confirmDelete(QWidget *parent=0,QString message = QString("ATTENTION : Êtes-vous sûr de vouloir supprimer cet élément ?"));
    static bool confirmUpdate(QWidget *parent=0,QString message = QString("CONFIRM. : Êtes-vous sûr de vouloir modifier cet élément ?"));

};

#endif // MESSAGEBOX_H
