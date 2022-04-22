#include "mytablemodel.h"


int TableModel::rowCount(const QModelIndex &) const
{
    return 8;
}

int TableModel::columnCount(const QModelIndex &) const
{
    return 8;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    switch (role) {
    case Qt::BackgroundRole:
        if ((index.column() + index.row()) % 2 != 0)
            return "grey";
        else
            return "white";
//    case myRole1:

//        return "RED";
//    case myRole2:
//        return "Поплавляйтесь, ";
//        //return "Indices: ";
    default:
        break;
    }

    return QVariant();
}

QHash<int, QByteArray> TableModel::roleNames() const
{
    return {
            {Qt::BackgroundRole, "myColor"},
    };
}
