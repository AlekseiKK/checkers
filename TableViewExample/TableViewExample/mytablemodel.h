#include <qqml.h>
#include <QAbstractTableModel>
#include <QColor>
#include <QAbstractItemModel>

Q_DECLARE_METATYPE(QModelIndex)

class TableModel : public QAbstractTableModel
{
    Q_OBJECT




    //Про преобразования типов между C++ и qml https://doc.qt.io/qt-5/qtqml-cppintegration-data.html

    enum MyRoles {
        myRole1 = Qt::UserRole,
        myRole2,
        myRole3,
        myRole4,
    };

public:
    Q_INVOKABLE void outIndex(const QVariant &index);

    int rowCount(const QModelIndex & = QModelIndex()) const override;

    int columnCount(const QModelIndex & = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;


signals:
    void textChanged();
private:
    QString m_text = QStringLiteral("first version of my text");
    QVector<int> m_board = {0,1,0,0,0,2,0,2,
                            1,0,1,0,0,0,2,0,
                            0,1,0,0,0,2,0,2,
                            1,0,1,0,0,0,2,0,
                            0,1,0,0,0,2,0,2,
                            1,0,1,0,0,0,2,0,
                            0,1,0,0,0,2,0,2,
                            1,0,1,0,0,0,2,0
     };
};
