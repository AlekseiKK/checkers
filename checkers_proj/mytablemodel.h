#include <qqml.h>
#include <QAbstractTableModel>
#include <QColor>
#include <QAbstractItemModel>


Q_DECLARE_METATYPE(QModelIndex)

class TableModel : public QAbstractTableModel
{
    Q_OBJECT


    Q_PROPERTY(QString score_of_first READ score_of_first NOTIFY score_of_firstChanged)
    Q_PROPERTY(QString score_of_second READ score_of_second NOTIFY score_of_secondChanged)
    Q_PROPERTY(bool end_of_game READ end_of_game NOTIFY end_of_gameChanged)
    bool end_of_game();
    QString score_of_second();
    QString score_of_first();

    enum MyRoles {
        myRole1 = Qt::UserRole,
        myRole2,
        myRole3,
        myRole4,
    };

public:
    Q_INVOKABLE void setBoard(QString color_of_player); // установка состояния доски
    Q_INVOKABLE void move(const QVariant &index); // реализация перемещения шашки
    Q_INVOKABLE void show_places(const QVariant &index); // показать возможные ходы
    bool game_over(); // проверка закончилась ли игра
    bool is_queen(int index); // проверка шашки на королеву
    void make_queen(int index); // превращение в королеву
    bool at_the_board_edge(int index); // проверка находится ли шашка на крае доски
    void show_possible_moves(const QVariant &index); // показать возможные клетки для перемещения
    void attack(int index); // реализация атаки
    bool check_every_checker_for_attack(); // проверка всех шашек, есть атакующие или нет
    void create_places_for_moves(int index); // создать клетки для перемещения обычной пешки
    void create_places_for_queen_moves(int index); // создать клетки для перемещения королевы
    void create_places_for_queen_attack(int index); // создать клетки для атаки королевы
    void create_places_for_attack(int index); // cоздать клетки для атаки обычной пешки
    void check_checkers_around(int index, int checker_color); // проверка всех соседних диагональных клеток
    void pass_the_move();  // передать ход
    int reverse_checker(int checker_color); // возвращает обратный цвет пешки
    void hide_places_for_moves(); // скрыть все места для перемещения
    bool should_attack(int index, int enemy_checker_color); // проверка должна ли пешка или королева атаковать
    int rowCount(const QModelIndex & = QModelIndex()) const override;
    int columnCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    bool posible_index(int index); // проверка нахождения пешки или королевы на доске
signals:
    void score_of_firstChanged(QString first_player_score); // сигнал об изменение счёта первого игрока
    void score_of_secondChanged(QString second_player_score); // сигнал об изменение счёта второго игрока
    bool end_of_gameChanged(bool end); // сигнал о окончание партии
private:
    bool end = false;
    QString first_player_score;
    QString second_player_score;
    int points_of_first = 0;
    int points_of_second = 0;
    const int m_black = 1;
    const int m_white = 2;
    int current_player = 2; // начинают всегда белые (2) - белый цвет, (1) - черный
    int current_checker = -1; // текущаю выбранная фишка
    int first_player_color = 2; // по умолчанию первый игрок если не изменит цвет играет за белых
    int count_of_white_checkers = 12;
    int count_of_black_checkers = 12;
    QVector<int> indices_of_neighboring_checkers = {-7, -9, 7, 9}; // вектор индексов соседних фишек
    QVector<int> m_board = {0,1,0,0,0,2,0,2,
                            1,0,1,0,0,0,2,0,
                            0,1,0,0,0,2,0,2,
                            1,0,1,0,0,0,2,0,
                            0,1,0,0,0,2,0,2,
                            1,0,1,0,0,0,2,0,
                            0,1,0,0,0,2,0,2,
                            1,0,1,0,0,0,2,0};

};
