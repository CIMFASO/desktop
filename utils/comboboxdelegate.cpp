#include "comboboxdelegate.h"

ComboBoxDelegate::ComboBoxDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{

}
ComboBoxDelegate::~ComboBoxDelegate()
{
    //editor = new QComboBox();
}

QWidget *ComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QComboBox *editor = new QComboBox(parent);
    editor->setFrame(false);
    editor->setModel(model);
    return editor;
}

void ComboBoxDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    /*QComboBox *editor = new QComboBox();
    editor->setFrame(false);
    editor->setModel(model);
    editor->setGeometry(option.rect);

    if(option.state == QStyle::State_Selected)
    {
        painter->fillRect(option.rect,option.palette.highlight());
    }

    QPixmap map = editor->grab();
    painter->setBrush(Qt::white);
    painter->drawPixmap(option.rect.x(),option.rect.y(),map);*/

    //painter->setBrush(Qt::white);
    painter->drawText(option.rect,index.data(Qt::DisplayRole).toString(),QTextOption(Qt::AlignCenter));
}

void ComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString value = index.model()->data(index, Qt::EditRole).toString();
    QComboBox *combo = static_cast<QComboBox*>(editor);
    combo->setCurrentText(value);
}

void ComboBoxDelegate::setModelData(QWidget *e, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *combo = static_cast<QComboBox*>(e);
    QString value = combo->currentText();
    //editor->setCurrentText(value);
    model->setData(index, value, Qt::DisplayRole);
    emit dataChanged(value,index);
}

void ComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

void ComboBoxDelegate::setModel(QAbstractItemModel *value)
{
    model = value;
}
