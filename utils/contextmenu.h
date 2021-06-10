#ifndef CONTEXMENU_H
#define CONTEXMENU_H

#include <QMenu>
#include <QAction>
#include <QVariant>
#include <QTableView>
#include <QModelIndex>

class ContextMenu : public QObject
{
    Q_OBJECT
public:
    ContextMenu(QWidget *parent = nullptr);

    void setupMenu(QTableView *table,const QPoint &pos);
    int getSelectedItemId();

public:
    void addAction(const QString name);
    void hideAction(const QString name);
    void showAction(const QString name);
    QAction* getActionByName(const QString name);
    QList<QAction *> getActions() const;
    void setActions(const QList<QAction *> &value);

private slots:
    void slotDelete();
    void slotUpdate();
signals:
    void deleteTriggered();
    void updateTriggered();

private:
    int selectedId;
    QMenu *menu;
    QAction *modifier;
    QAction *supprimer;
    QList<QAction *> actions;
};

#endif // CONTEXMENU_H
