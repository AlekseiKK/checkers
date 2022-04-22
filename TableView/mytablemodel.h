#include <qqml.h>
#include <QAbstractTableModel>
#include <QColor>

class TableModel : public QAbstractTableModel
{
    Q_OBJECT

    enum MyRoles{
        myRole1 = Qt::UserRole,
        myRole2,
        myRole3
    };

public slots:
    void receiveFromQml();
public:

    int rowCount(const QModelIndex & = QModelIndex()) const override;

    int columnCount(const QModelIndex & = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;
private:
    QVector<QVector<int>> m_board = {{0,1,0,1,0,1,0,1},
                                     {1,0,1,0,1,0,1,0},
                                     {0,1,0,1,0,1,0,1},
                                     {0,0,0,0,0,0,0,0},
                                     {0,0,0,0,0,0,0,0},
                                     {2,0,2,0,2,0,2,0},
                                     {0,2,0,2,0,2,0,2},
                                     {2,0,2,0,2,0,2,0}
                                    };
    int count = 0;
};
