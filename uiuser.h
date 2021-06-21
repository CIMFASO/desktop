#ifndef UIUSER_H
#define UIUSER_H
#include <QDialog>
#include "dao/handledata.h"
#include "models/user.h"
#include <QStandardItemModel>
#include "models/modulemanager.h"
#include "utils/contextmenu.h"
#include "utils/waitingspinnerwidget.h"
#include "utils/customdelegate.h"

namespace Ui {
class User;
}
namespace UI {
    class User: public QDialog, public HandleData<Model::User>

    {

        Q_OBJECT
    public:
        explicit User(QWidget *parent = nullptr);
        ~User();

        void addUserDefaultAccessRules();
    public slots:
        void slotUpdate(const QModelIndex &index) override;
        void slotDelete(const QModelIndex &index) override;
        void httpResponse(QMap<QString,QByteArray> response) override;
        void on_usertableView_customContextMenuRequested(const QPoint &pos);
        void clearFields();

    public slots:
        void on_annulerpushButton_clicked();
        void on_ajouterpushButton_clicked();
    private slots:
        void on_confirmationMdpLineEdit_textChanged(const QString &arg1);
        void on_motDePasseLineEdit_textChanged(const QString &arg1);

    private:
        Ui::User *ui;
        QStandardItemModel * model;
        Model::ModuleManager *moduleManager;
        WaitingSpinnerWidget *spinner;
        CustomDelegate *delegate;
        int idUser = 0;
    };
}
#endif // USER_H
