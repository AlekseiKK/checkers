#include "mytablemodel.h"

int TableModel::rowCount(const QModelIndex &) const
{
    return 10;
}

int TableModel::columnCount(const QModelIndex &) const
{
    return 10;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    switch (role) {
    case Qt::DisplayRole:
        return "чмок";
        //return QString("%1, %2").arg(index.column()).arg(index.row());
    case Qt::TextColorRole:
        return QColor(index.column() * 20, index.column() * 10 + index.row() * 10, index.row() * 20);
    case myRole1:
        return "RED";
    case myRole2:
        return "Поплавляйтесь, ";
        //return "Indices: ";
    default:
        break;
    }

    return QVariant();
}

QHash<int, QByteArray> TableModel::roleNames() const
{
    return { {Qt::DisplayRole, "myDisplay"},
            {Qt::ForegroundRole, "myColor"},
            {myRole1, "myTextColor"},
            {myRole2, "myPrefix"}
    };
}
