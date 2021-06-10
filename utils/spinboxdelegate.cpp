#include "spinboxdelegate.h"

SpinBoxDelegate::SpinBoxDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{

}

SpinBoxDelegate::~SpinBoxDelegate()
{

}

QWidget *SpinBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSpinBox *editor = new QSpinBox(parent);
    editor->setRange(min,max);
    editor->setFrame(false);
    return editor;
}

void SpinBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    double value = index.model()->data(index, Qt::EditRole).toDouble();
    QSpinBox *s = static_cast<QSpinBox*>(editor);
    s->setValue(value);
}

void SpinBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QSpinBox *s = static_cast<QSpinBox*>(editor);
    double value = s->value();
    model->setData(index, value, Qt::EditRole);
    emit dataChanged(index,value);
}

void SpinBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

void SpinBoxDelegate::setSpinBoxRange(int min, int max)
{
    this->min = min;
    this->max = max;
}
