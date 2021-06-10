#include "contextmenu.h"

ContextMenu::ContextMenu(QWidget *parent)
{
    menu = new QMenu(parent);
    modifier  = new QAction("Modifier");
    supprimer = new QAction("Supprimer");
    actions << modifier << supprimer;
    connect(modifier, &QAction::triggered, [=]() {emit slotUpdate();});
    connect(supprimer, &QAction::triggered, [=]() {emit slotDelete();});
}

void ContextMenu::setupMenu(QTableView *table, const QPoint &pos)
{
    menu->addAction(modifier);
    menu->addAction(supprimer);
    QModelIndex index = table->selectionModel()->currentIndex();

    selectedId = index.sibling(index.row(),0).data().toInt();
    if(selectedId > 0)
    {
        menu->popup(table->viewport()->mapToGlobal(pos));
    }
}

int ContextMenu::getSelectedItemId()
{
    return  selectedId;
}

void ContextMenu::addAction(const QString name)
{
    QAction *action = new QAction(name);
    actions.append(action);
    menu->addAction(action);
}

void ContextMenu::hideAction(const QString name)
{
    getActionByName(name)->setVisible(false);
}

void ContextMenu::showAction(const QString name)
{
    getActionByName(name)->setVisible(true);
}

QAction *ContextMenu::getActionByName(const QString name)
{
    for(QAction *a : actions){
        if(a->text() == name)
            return a;
    }

    return new QAction();
}

void ContextMenu::slotDelete()
{
    emit deleteTriggered();
}

void ContextMenu::slotUpdate()
{
    emit updateTriggered();
}

QList<QAction *> ContextMenu::getActions() const
{
    return actions;
}

void ContextMenu::setActions(const QList<QAction *> &value)
{
    actions = value;
}
