#ifndef LINEEDITDELEGATE_H
#define LINEEDITDELEGATE_H

#include <QStyledItemDelegate>
#include <QLineEdit>

class LineEditDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    LineEditDelegate(QObject *parent = nullptr);
    ~LineEditDelegate();

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const override;

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const override;

    QValidator *getValidator() const;
    void setValidator(QValidator *value);

private:
    QValidator *validator = nullptr;
signals:
    void dataChanged(const QModelIndex &index,QString value) const;
};


#endif // LINEEDITDELEGATE_H
