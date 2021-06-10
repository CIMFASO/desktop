#include "checkboxdelegate.h"

CheckBoxDelegate::CheckBoxDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{

}
CheckBoxDelegate::~CheckBoxDelegate()
{

}

QWidget *CheckBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QCheckBox *editor = new QCheckBox(parent);
    return editor;
}

void CheckBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    bool value = index.model()->data(index, Qt::EditRole).toBool();
    QCheckBox *check = static_cast<QCheckBox*>(editor);
    check->setChecked(value);
}

void CheckBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QCheckBox *check = static_cast<QCheckBox*>(editor);
    bool value = check->isChecked();
    model->setData(index, value, Qt::DisplayRole);
    emit dataChanged(index,value);
}

void CheckBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

void CheckBoxDelegate::setModel(QAbstractItemModel *value)
{
    model = value;
}
