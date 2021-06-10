#include "lineeditdelegate.h"

LineEditDelegate::LineEditDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
    validator = new QRegExpValidator(parent);
}

LineEditDelegate::~LineEditDelegate()
{

}

QWidget *LineEditDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QLineEdit *editor = new QLineEdit(parent);
    editor->setFrame(false);
    editor->setValidator(validator);
    return editor;
}

void LineEditDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    double value = index.model()->data(index, Qt::EditRole).toDouble();
    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
    lineEdit->setText(QString::number(value));
}

void LineEditDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
    QString value = lineEdit->text().trimmed();
    model->setData(index, value, Qt::DisplayRole);
    emit dataChanged(index,value);
}

void LineEditDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

QValidator *LineEditDelegate::getValidator() const
{
    return validator;
}

void LineEditDelegate::setValidator(QValidator *value)
{
    validator = value;
}
