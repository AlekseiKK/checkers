#include "mytablemodel.h"



void TableModel::receiveFromQml()
{
    qDebug() << "Date:";
}

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
    case myRole1:
        if (m_board[index.row()][index.column()] != 0)
            return true;
        return false;
    case myRole2:
        if (m_board[index.row()][index.column()] == 1){
            return "black";
        }
        if (m_board[index.row()][index.column()] == 2){
            return "white";
        }

    default:
        break;
    }

    return QVariant();
}

QHash<int, QByteArray> TableModel::roleNames() const
{
    return {
            {Qt::BackgroundRole, "myColor"},
            {myRole1, "visibility"},
            {myRole2, "figcolor"}
    };
}
