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
private slots:
    void on_actionListe_des_B_L_triggered();

    void on_actionTaille_de_police_triggered();

    void on_actionTransporteur_triggered();

    void on_actionDestination_triggered();

    void on_actionFactures_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
