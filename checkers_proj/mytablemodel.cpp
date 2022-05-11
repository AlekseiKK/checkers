#include "mytablemodel.h"
#include <QDebug>
#include <QtWidgets/QMessageBox>


bool TableModel::end_of_game()
{
    return end;
}

QString TableModel::score_of_second()
{
    second_player_score.setNum(points_of_second);
    return second_player_score;
}

bool TableModel::can_move(const QVariant &index)
{
   if (m_board[index.value<int>()] == 3){return true;}
   return false;
}

QString TableModel::score_of_first()

{
    first_player_score.setNum(points_of_first);
    return first_player_score;
}


void TableModel::setBoard(QString color_of_player)
{
    count_of_white_checkers = 12;
    count_of_black_checkers = 12;
    current_player = 2;
    beginResetModel();
    if (color_of_player == "white" || first_player_color == 2){
        m_board = {0,1,0,0,0,2,0,2,
                   1,0,1,0,0,0,2,0,
                   0,1,0,0,0,2,0,2,
                   1,0,1,0,0,0,2,0,
                   0,1,0,0,0,2,0,2,
                   1,0,1,0,0,0,2,0,
                   0,1,0,0,0,2,0,2,
                   1,0,1,0,0,0,2,0};
        first_player_color = 2;
    }
    if (color_of_player == "black" || first_player_color == 1){
        m_board = {0,2,0,0,0,1,0,1,
                   2,0,2,0,0,0,1,0,
                   0,2,0,0,0,1,0,1,
                   2,0,2,0,0,0,1,0,
                   0,2,0,0,0,1,0,1,
                   2,0,2,0,0,0,1,0,
                   0,2,0,0,0,1,0,1,
                   2,0,2,0,0,0,1,0};
        first_player_color = 1;
    }
    endResetModel();

}

void TableModel::move(const QVariant &index)
{
    if (current_checker != -1){
        beginResetModel();
        if (should_attack(current_checker, reverse_checker(current_player)))
        {

            if (m_board[index.value<int>()] == 3 && (m_board[current_checker] == current_player || m_board[current_checker] == current_player * 10))
            {
                if (!is_queen(m_board[current_checker])){make_queen(index.value<int>());}
                m_board[index.value<int>()] = m_board[current_checker];
                attack(index.value<int>());
                if (current_player == 2){
                    count_of_black_checkers -=1;
                }
                else{
                    count_of_white_checkers -=1;
                }
                if (game_over()){
                    qDebug() << "end";
                }
                hide_places_for_moves();
                m_board[current_checker] = 0;
                current_checker = index.value<int>();
                if (should_attack(current_checker, reverse_checker(current_player)))
                {
                    show_possible_moves(current_checker);
                }
                else{
                    pass_the_move();
                }
            }
        }
        else
        {
            if (m_board[index.value<int>()] == 3 && (m_board[current_checker] == current_player || m_board[current_checker] == current_player * 10))
            {
                if (!is_queen(m_board[current_checker])){make_queen(index.value<int>());}
                m_board[index.value<int>()] = m_board[current_checker];
                hide_places_for_moves();
                m_board[current_checker] = 0;
                current_checker = index.value<int>();
                pass_the_move();
            }
        }
        endResetModel();
    }

}

void TableModel::show_places(const QVariant &index)
{

    hide_places_for_moves();
    beginResetModel();
    if (check_every_checker_for_attack() && should_attack(index.value<int>(), reverse_checker(current_player))){
        show_possible_moves(index);
    }
    else if (!check_every_checker_for_attack()){
        show_possible_moves(index);
    }
    endResetModel();

}

bool TableModel::game_over()
{
    if (count_of_black_checkers == 0 || count_of_white_checkers == 0){
        if (first_player_color == 1 && count_of_black_checkers == 0 || first_player_color == 2 && count_of_white_checkers == 0)
        {
            points_of_second += 1;
            emit score_of_secondChanged(second_player_score.setNum(points_of_second));
        }
        else
        {
            points_of_first += 1;
            emit score_of_firstChanged(first_player_score.setNum(points_of_first));
        }
        end = true;
        emit end_of_gameChanged(end);
        return true;
    }
       return false;
}

bool TableModel::is_queen(int index)
{
    if ((m_board[index] == 10 && current_player == 1) || (m_board[index] == 20 && current_player == 2)){return true;}
    else{return false;}
}

void TableModel::make_queen(int index)
{
    if ((index + 1) % 8 == 0 && current_player == 1 && first_player_color == 2)
    {
        m_board[current_checker] = 10;
    }
    else if (index % 8 == 0 && current_player == 2 && first_player_color == 2)
    {
        m_board[current_checker] = 20;
    }
    else if ((index + 1) % 8 == 0 && current_player == 2 && first_player_color == 1)
    {
        m_board[current_checker] = 20;
    }
    else if (index % 8 == 0 && current_player == 1 && first_player_color == 1)
    {
        m_board[current_checker] = 10;
    }
}

bool TableModel::at_the_board_edge(int index)
{
    if ((index >= 0 && index <= 7) || (index % 8 == 0) || ((index + 1) % 8 == 0) || (index >= 56 && index <= 63)){return true;}
    else{return false;}
}

void TableModel::show_possible_moves(const QVariant &index)
{
    beginResetModel();

    if (current_checker == -1 || current_checker == index)
    {
        current_checker = index.value<int>();
        if (should_attack(current_checker, reverse_checker(m_board[current_checker])))
        {
            if (is_queen(current_checker))
            {
                create_places_for_queen_attack(index.value<int>());
            }
            else
            {
               create_places_for_attack(index.value<int>());
            }

        }
        else
        {
            if (is_queen(current_checker)){create_places_for_queen_moves(index.value<int>());}
            else{create_places_for_moves(index.value<int>());}
        }
    }
    else if (current_checker != index.value<int>()){
        current_checker = index.value<int>();
        if (should_attack(current_checker, reverse_checker(m_board[current_checker])))
        {
            if (is_queen(current_checker)){
                create_places_for_queen_attack(current_checker);
            }
            else
            {
                create_places_for_attack(index.value<int>());
            }
        }
        else
        {
            if (is_queen(current_checker)){
                create_places_for_queen_moves(current_checker);
            }
            else
            {
                create_places_for_moves(index.value<int>());
            }

        }

    }
    endResetModel();
}

void TableModel::attack(int index)
{
    if (is_queen(current_checker))
    {
        if ((index - current_checker) % 7 == 0 && (index - current_checker < 0))
        {
            for (int i = current_checker - 7; i > index; i -= 7){
                m_board[i] = 0;
            }
        }
        if ((index - current_checker) % 7 == 0 && (index - current_checker > 0))
        {
            for (int i = current_checker + 7; i < index; i += 7){
                m_board[i] = 0;
            }
        }
        if ((index - current_checker) % 9 == 0 && (index - current_checker > 0))
        {


            for (int i = current_checker + 9; i < index; i += 9){

                m_board[i] = 0;
            }
        }
        if ((index - current_checker) % 9 == 0 && (index - current_checker < 0))
        {
            for (int i = current_checker - 9; i > index; i -= 9){
                m_board[i] = 0;
            }
        }


    }
    else{
        if (index - current_checker == -14){
            m_board[current_checker - 7] = 0;
        }
        else if (index - current_checker == 18){
            m_board[current_checker + 9] = 0;
        }
        else if (index - current_checker == -18){
            m_board[current_checker - 9] = 0;
        }
        else if (index - current_checker == 14){
            m_board[current_checker + 7] = 0;
        }
    }
}

bool TableModel::check_every_checker_for_attack()
{
    for(int i = 0; i < 64; i++){
        if (should_attack(i, reverse_checker(m_board[i])))
        {
            if (m_board[i] == current_player || m_board[i] == current_player * 10){
                return true;
            }
        }
    }
    return false;

}



void TableModel::create_places_for_moves(int index)
{
    if (current_player == 1 && m_board[current_checker] == 1 && (index + 1) % 8 != 0 && (first_player_color == 2)){
        if (m_board[index] != 0)
        {
            if (posible_index(index - 7) && m_board[index - 7] == 0){
                m_board[index - 7] = 3;
            }
            if (posible_index(index + 9) && m_board[index + 9] == 0){
                m_board[index + 9] = 3;
            }
        }
    }
    else
        if (current_player == 2 && m_board[current_checker] == 2 && index % 8 != 0 && (first_player_color == 2)){
        {
            if (m_board[index] != 0)
            {
                if (posible_index(index + 7) && m_board[index + 7] == 0)
                    m_board[index + 7] = 3;
                if (posible_index(index - 9) && m_board[index - 9] == 0)
                    m_board[index - 9] = 3;
            }
        }
        }
    if (current_player == 2 && m_board[current_checker] == 2 && (index + 1) % 8 != 0 && (first_player_color == 1)){
        if (m_board[index] != 0)
        {
            if (posible_index(index - 7) && m_board[index - 7] == 0){
                m_board[index - 7] = 3;
            }
            if (posible_index(index + 9) && m_board[index + 9] == 0){
                m_board[index + 9] = 3;
            }
        }
    }
    else
        if (current_player == 1 && m_board[current_checker] == 1 && index % 8 != 0 && (first_player_color == 1)){
        {
            if (m_board[index] != 0)
            {
                if (posible_index(index + 7) && m_board[index + 7] == 0)
                    m_board[index + 7] = 3;
                if (posible_index(index - 9) && m_board[index - 9] == 0)
                    m_board[index - 9] = 3;
            }
        }
        }

}

void TableModel::create_places_for_queen_moves(int index)
{
    for (int i = 0; i < 4; i++){
        index = current_checker;
        index = index + indices_of_neighboring_checkers[i];
        while (posible_index(index) && m_board[index] == 0){
            if ((index / 8  + index % 8) % 2 == 0){break;}
            m_board[index] = 3;
            if (at_the_board_edge(index)){break;}
            index += indices_of_neighboring_checkers[i];
        }
    }
}

void TableModel::create_places_for_queen_attack(int index)
{
    int enemy_checker_color = reverse_checker(current_player);
    for (int i = 0; i < 4; i++){
        int index_1 = index + indices_of_neighboring_checkers[i];
        bool enemy_at_line = false;
        while (posible_index(index_1) && (index_1 / 8  + index_1 % 8) % 2 != 0 && !at_the_board_edge(index_1)){
            if (m_board[index_1] == current_player || m_board[index_1] == current_player* 10){
                break;
            }
            if (m_board[index_1] == enemy_checker_color || m_board[index_1] == enemy_checker_color * 10){
                enemy_at_line = true;
                break;
            }
            index_1 += indices_of_neighboring_checkers[i];
        }
        if (enemy_at_line){
            while (posible_index(index_1) && (index_1 / 8  + index_1 % 8) % 2 != 0){
                index_1 += indices_of_neighboring_checkers[i];
                qDebug() << index_1;
                if (posible_index(index_1) && (index_1 / 8  + index_1 % 8) % 2 != 0){
                    if (m_board[index_1] != 0){
                        qDebug() << "breaaak";
                        break;
                    }
                    m_board[index_1] = 3;
                }
            }
        }
    }
}

void TableModel::create_places_for_attack(int index)
{
    if (current_player == 1 && m_board[current_checker] == 1)
    {
        if (m_board[index] != 0){check_checkers_around(index, m_white);}
    }
    else if (current_player == 2 && m_board[current_checker] == 2)
        {
            if (m_board[index] != 0){check_checkers_around(index, m_black);}
        }
}

void TableModel::check_checkers_around(int index, int checker_color)
{
    if (m_board[index] != 0)
    {
        for (int i = 0; i < 4; i ++)
        {
            if (posible_index(index + indices_of_neighboring_checkers[i])
                    && (m_board[index + indices_of_neighboring_checkers[i]] == checker_color || m_board[index + indices_of_neighboring_checkers[i]] == checker_color * 10))
            {
                if (posible_index(index + 2 * indices_of_neighboring_checkers[i]) && m_board[index + 2 * indices_of_neighboring_checkers[i]] == 0)
                {
                    if ((checker_color == m_white || checker_color == m_white * 10 )&& ((index + indices_of_neighboring_checkers[i]) + 1) % 8 != 0){
                        m_board[index + 2 * indices_of_neighboring_checkers[i]] = 3;
                    }
                    else if ((checker_color == m_black || checker_color == m_black * 10) && (index + indices_of_neighboring_checkers[i]) % 8 != 0){
                        m_board[index + 2 * indices_of_neighboring_checkers[i]] = 3;
                    }

                }
            }
        }
    }
}

void TableModel::pass_the_move()
{
    if (current_player == 2){
        current_player = 1;
    }
    else{
        current_player = 2;
    }


}

int TableModel::reverse_checker(int checker_color)
{
   if (checker_color == 1 || checker_color == 10){return 2;}
   else {return 1;}

}

void TableModel::hide_places_for_moves()
{
    for (int i = 0; i <= 63; i++){
        if (m_board[i] == 3){
            m_board[i] = 0;
        }
    }
}



bool TableModel::should_attack(int index, int enemy_checker_color)
{

    if (m_board[index] != 0 && !is_queen(index))
    {
        for (int i = 0; i < 4; i++){
            if (posible_index(index + indices_of_neighboring_checkers[i])
                    && (m_board[index + indices_of_neighboring_checkers[i]] == enemy_checker_color
                        || m_board[index + indices_of_neighboring_checkers[i]] == enemy_checker_color * 10))
            {
                if (posible_index(index + (2 * indices_of_neighboring_checkers[i])) &&
                        (m_board[index + (2 * indices_of_neighboring_checkers[i])] == 0 || m_board[index + (2 * indices_of_neighboring_checkers[i])] == 3))
                {
                    if (!at_the_board_edge(index + indices_of_neighboring_checkers[i])){return true;}
                }
            }
        }
    }
    else if(m_board[index] != 0 && is_queen(index)){
        for (int i = 0; i < 4; i++)
        {
            int index_1 = index + indices_of_neighboring_checkers[i];
            bool enemy_at_line = false;
            while (posible_index(index_1) && (index_1 / 8  + index_1 % 8) % 2 != 0 && !at_the_board_edge(index_1))
            {
                if (m_board[index_1] == current_player || m_board[index_1] == current_player* 10)
                {
                    break;
                }
                if (m_board[index_1] == enemy_checker_color || m_board[index_1] == enemy_checker_color * 10)
                {
                    enemy_at_line = true;
                    break;
                }
                index_1 += indices_of_neighboring_checkers[i];
            }
            if (enemy_at_line)
            {
                index_1 += indices_of_neighboring_checkers[i];
                if (posible_index(index_1) && (index_1 / 8  + index_1 % 8) % 2 != 0 && (m_board[index_1] == 0 || m_board[index_1] == 3))
                {
                    return true;
                }
            }
        }
    }

    return false;
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
        if (m_board[index.column() * 8 + index.row()] == 1 || m_board[index.column() * 8 + index.row()] == 10){
            return "black";
        }
        if (m_board[index.column() * 8 + index.row()] == 2 || m_board[index.column() * 8 + index.row()] == 20){
            return "white";
        }
    case myRole3:
        if (m_board[index.column() * 8 + index.row()] == 10 || m_board[index.column() * 8 + index.row()] == 20)
        {
            return true;
        }
        else{
            return false;
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
            {myRole3, "starvisibility"},
            {myRole4, "bordwidth"}
    };
}

bool TableModel::posible_index(int index)
{
    if ((index >= 0) && (index <= 63)){
        return true;
    }
    return false;
}


