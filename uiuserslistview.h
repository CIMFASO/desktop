#ifndef UIUSERSLISTVIEW_H
#define UIUSERSLISTVIEW_H

#include <QDialog>
#include "utils/messagebox.h"
#include "dao/handledata.h"
#include "models/user.h"
#include "utils/customdelegate.h"
#include "utils/waitingspinnerwidget.h"
#include <QSortFilterProxyModel>

namespace Ui {
class UIUsersListview;
}

class UIUsersListview : public QDialog,public HandleData<Model::User>
{
    Q_OBJECT

public:
    explicit UIUsersListview(QWidget *parent = nullptr);
    ~UIUsersListview();

private slots:
    void httpResponse(QMap<QString, QByteArray>) override;
    void slotUpdate(const QModelIndex &) override;
    void slotDelete(const QModelIndex &) override;

    void on_newButton_clicked();
    void on_nomLineEdit_textChanged(const QString &arg1);

signals:
    void success();

private:
    Ui::UIUsersListview *ui;
    WaitingSpinnerWidget *spinner;
    CustomDelegate *delegate;
    QSortFilterProxyModel *sortModel;
};

#endif // UIUSERSLISTVIEW_H
