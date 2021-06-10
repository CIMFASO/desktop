#ifndef CUSTOMLISTMODEL_H
#define CUSTOMLISTMODEL_H

#include <QAbstractListModel>
#include <QObject>

template<class T>
class CustomListModel : public QAbstractListModel
{
public:
    explicit CustomListModel() {}
    ~CustomListModel() {}

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override
    {
        // For list models only the root node (an invalid parent) should return the list's size. For all
        // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
        if (parent.isValid())
            return 0;

        return list.size();
    }
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override
    {
        if (!index.isValid())
            return QVariant();

        if((role == Qt::DisplayRole) && (index.row() < list.size()))
            return list.at(index.row()).getLabel();

        if((role == Qt::UserRole)  && (index.row() < list.size()))
            return list.at(index.row()).getId();

        return QVariant();
    }
    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,int role = Qt::EditRole) override
    {
        if (data(index, role) != value) {
            // FIXME: Implement me!
            emit dataChanged(index, index, QVector<int>() << role);
            return true;
        }
        return false;
    }

public:
    void append(const T &value,const QModelIndex &index = QModelIndex())
    {
        beginInsertRows(index,list.size(),list.size());
        list.append(value);
        endInsertRows();
    }
    void pop(const QModelIndex &index)
    {
        if(list.size() > 0){
            beginRemoveRows(index,list.size()-1,list.size()-1);
            list.pop_back();
            endRemoveRows();
        }
    }

    void clear()
    {
        beginRemoveRows(QModelIndex(),0,list.size()-1);
        list.clear();
        endRemoveRows();
    }

    T at(const int &index)
    {
        if(index >= 0 && index < list.size()){
            return list.at(index);
        }else
            return T();
    }
    T getById(const int &id)
    {
        for(T model : list){
            if(model.getId() == id){
                return model;
            }
        }

        return T();
    }
    T getByLabel(const QString &label)
    {
        for(T model : list){
            if(model.getLabel() == label){
                return model;
            }
        }
        return T();
    }

private:
    QList<T> list;
};

#endif // CUSTOMLISTMODEL_H
