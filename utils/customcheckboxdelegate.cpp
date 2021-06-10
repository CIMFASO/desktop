#include "customcheckboxdelegate.h"

#include <QApplication>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QDebug>
#include <QPainter>

CustomCheckBoxDelegate::CustomCheckBoxDelegate(QObject *parent) : QStyledItemDelegate(parent)
{
    if(QTableView *tableView = qobject_cast<QTableView*>(parent))
    {
        view = tableView;

        widget = new QCheckBox(view);
        widget->setObjectName("check");

        widget->hide();

        view->setMouseTracking(true);

        connect(view,&QTableView::entered,this,&CustomCheckBoxDelegate::cellEntered);
        connect(widget,&QCheckBox::clicked,this,&CustomCheckBoxDelegate::slotCheckBoxClicked);

        isOneCellInEditMode = false;
    }
}

CustomCheckBoxDelegate::~CustomCheckBoxDelegate()
{
    delete widget;
}

void CustomCheckBoxDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.column() == customColumn){

        widget->setGeometry(option.rect);
        widget->setObjectName("check");

        if(option.state == QStyle::State_Selected)
        {
            painter->fillRect(option.rect,option.palette.highlight());
        }

        QPixmap map = widget->grab();
        painter->setBrush(Qt::white);
        painter->drawPixmap(option.rect.x(),option.rect.y(),map);

    } else {
        QStyledItemDelegate::paint(painter, option, index);
    }
}

QWidget *CustomCheckBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.column() == customColumn)
    {
        QCheckBox *w = new QCheckBox(parent);
        w->setChecked(index.sibling(index.row(),customColumn).data().toBool());
        w->setObjectName("check");

        connect(widget,&QCheckBox::clicked,this,&CustomCheckBoxDelegate::slotCheckBoxClicked);

        return w;
    }
    else
    {
        return QStyledItemDelegate::createEditor(parent,option,index);
    }
}

void CustomCheckBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

void CustomCheckBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{

    QCheckBox *c = static_cast<QCheckBox*>(editor);
    c->setChecked(index.sibling(index.row(),customColumn).data().toBool());
    model->setData(index, c->isChecked(), Qt::EditRole);
    //emit dataChanged(model,index);
}

void CustomCheckBoxDelegate::setCustomColumn(int value)
{
    customColumn = value;
}

void CustomCheckBoxDelegate::cellEntered(const QModelIndex &index)
{
    if(index.column() == customColumn)
    {
        if(isOneCellInEditMode)
        {
            view->closePersistentEditor(currentEditedCellIndex);
        }
        view->openPersistentEditor(index);
        isOneCellInEditMode = true;
        currentEditedCellIndex = index;
    }
    else
    {
        if(isOneCellInEditMode)
        {
            isOneCellInEditMode = false;
            view->closePersistentEditor(currentEditedCellIndex);
        }
    }
}
