#include "mytablemodel.h"
#include <QDebug>



void TableModel::outIndex(const QVariant &index)
{
    beginResetModel();
    qDebug() << index.value<int>();
    qDebug() << m_board[index.value<int>()];
    int row = index.value<int>() % 8;
    int col = index.value<int>() / 8;
    if (m_board[index.value<int>()] == 2){
        m_board[index.value<int>()] = 1;
        qDebug() << row << col;
    }
   endResetModel();
   //emit dataChanged(createIndex(row, col), createIndex(row, col));
   qDebug() << m_board[index.value<int>()];
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
        if (m_board[index.column() * 8 + index.row()] != 0 && m_board[index.column() * 8 + index.row()] != 3)
            return true;
        return false;
    case myRole2:
        if (m_board[index.column() * 8 + index.row()] == 1){
            return "black";
        }
        if (m_board[index.column() * 8 + index.row()] == 2){
            return "white";
        }
    case myRole4:
    {
        if (m_board[index.column() * 8 + index.row()] == 3){
            return 5;
        }
        else{
            return 0;
        }
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
            {myRole2, "figcolor"},
            {myRole4, "bordwidth"}
    };
}


