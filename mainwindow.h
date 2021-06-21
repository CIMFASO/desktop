#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QMessageBox>
#include <utils.h>
#include <QCloseEvent>
#include <QFontDialog>
#include <QTextStream>
#include <QLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void closeEvent(QCloseEvent *event);
    void showWidgetInMainLayout(QWidget *w);
public slots:
    void hideActions();
private slots:
    void on_actionListe_des_B_L_triggered();
    void on_actionTaille_de_police_triggered();
    void on_actionTransporteur_triggered();
    void on_actionDestination_triggered();
    void on_actionFactures_triggered();
    void on_actionTaxes_triggered();
    void on_actionDeconnexion_triggered();
    void on_actionParam_trage_triggered();
    void on_actionSecurit_triggered();
    void on_actionEtats_Factures_triggered();

signals:
    void deconnexion();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
