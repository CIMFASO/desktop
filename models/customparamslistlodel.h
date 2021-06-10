#ifndef CUSTOMPARAMSLISTMODEL_H
#define CUSTOMPARAMSLISTMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include "models/typeparametreglobal.h"

class CustomParamsListModel : public QAbstractListModel
{
public:
    explicit CustomParamsListModel() {}
    ~CustomParamsListModel() {}

    enum CustomRoles {IdRole = Qt::UserRole+1,CodeRole,LibelleRole};
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
            return list.at(index.row()).getLibelle();

        if((role == CustomRoles::IdRole)  && (index.row() < list.size()))
            return list.at(index.row()).getIdType();

        if((role == CustomRoles::CodeRole) && (index.row() < list.size()))
            return list.at(index.row()).getCode();

        if((role == CustomRoles::LibelleRole)  && (index.row() < list.size()))
            return list.at(index.row()).getLibelle();
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
    void append(const Model::TypeParametreGlobal &value,const QModelIndex &index = QModelIndex())
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

    Model::TypeParametreGlobal at(const int &index)
    {
        if(index >= 0 && index < list.size()){
            return list.at(index);
        }else
            return Model::TypeParametreGlobal();
    }

    Model::TypeParametreGlobal getById(const int &id)
    {
        for(Model::TypeParametreGlobal model : list){
            if(model.getIdType() == id){
                return model;
                break;
            }
        }

        return Model::TypeParametreGlobal();
    }

    Model::TypeParametreGlobal getByCode(const QString &code)
    {
        for(Model::TypeParametreGlobal model : list){
            if(model.getCode() == code){
                return model;
                break;
            }
        }
        return Model::TypeParametreGlobal();
    }

private:
    QList<Model::TypeParametreGlobal> list;
};
#endif // CUSTOMPARAMSLISTMODEL_H
