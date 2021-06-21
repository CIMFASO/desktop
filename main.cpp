#include "mainwindow.h"

#include <QApplication>
#include <QSettings>
#include <QLocale>
#include <QStyleFactory>
#include <QTextStream>
#include <QTranslator>
#include <QLibraryInfo>
#include <QStandardPaths>
#include <QDir>
#include <QLibrary>
#include <QSettings>
#include "signin.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString locale = QLocale::system().name().section('_', 0, 0);
    QTranslator translator;
    translator.load(QString("qt_") + locale , QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    a.installTranslator(&translator);

    QCoreApplication::setOrganizationName("CIMFASO");
    QCoreApplication::setApplicationName("AppGestion");

    /*OxyInit init;
    init.createLogFile();
    qDebug() << init.getActivationKey();
    if(init.checkActivation("E62FF-E99E7-2B17B-9BEEC-46C76"))
        qDebug() << "KEY COOOOOOOOOOOOOOOOOOOOOOOOLLLLLLLLLLLLLLLL";
    else
        qDebug() << "KEY ERRORRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR";

    */

    /*Login login;
    OxygenMain w;

    QObject::connect(&login,SIGNAL(accepted()),&login,SLOT(hide()));
    QObject::connect(&login,&Login::accepted,&w,&OxygenMain::showMaximized);
    QObject::connect(&login,SIGNAL(rulesLoaded()),&w,SLOT(hideActions()));
    QObject::connect(&w,&OxygenMain::deconnexionClicked,&w,&OxygenMain::hide);
    QObject::connect(&w,&OxygenMain::deconnexionClicked,&login,&Login::show);*/

    MainWindow w;
    Login l;

    QObject::connect(&l,&Login::accepted,&l,&Login::hide);
    QObject::connect(&l,&Login::accepted,&w,&MainWindow::showMaximized);
    QObject::connect(&l,&Login::rulesLoaded,&w,&MainWindow::hideActions);
    QObject::connect(&w,&MainWindow::deconnexion,&w,&MainWindow::hide);
    QObject::connect(&w,&MainWindow::deconnexion,&l,&Login::show);

    QSettings settings;

    settings.setValue("host","localhost");
    settings.setValue("port","8080");

    QFont initial = QFont(
        settings.value("fontFamily","Calibri").toString(),
        settings.value("fontSize",13).toInt(),
        settings.value("fontBold",false).toInt(),
        settings.value("fontItalic",false).toBool()
    );

    QFile f(":/style/style.qss");
    if(!f.exists())
        printf("Fichier introuvable");
    else{
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        QString style = "";
        style += "QWidget{font: "+QString::number(initial.pointSize())+"px '"+initial.family()+"';}";
        style += ts.readAll();
        w.setStyleSheet(style);
    }

    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(path);
    if(!dir.exists())
        dir.mkpath(path);
    if(!dir.exists("AppGestion"))
        dir.mkdir("AppGestion");
    dir.cd("AppGestion");
    path = dir.absoluteFilePath("log.txt");
    if(QFile::exists(path))
        QFile::remove(path);

    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return 0;

    settings.setValue("logFilePath",path);

    QTextStream out(&file);
    out << "---------------------APPGESTION LOG FILE------------------" << "\n\n";

    l.show();
    return a.exec();
}
