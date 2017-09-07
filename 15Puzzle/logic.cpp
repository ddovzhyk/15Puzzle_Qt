#include "logic.h"

Logic::Logic(QObject *parent)
    : QAbstractListModel(parent)
{
//    for (int i = 0; i < NUMBER_CELLS; ++i)
//        cells << Cell();
    setStartCoordinates();
}

Logic::~Logic()
{
//    cells.clear();
}

int Logic::getBoardSize() const
{
    return BOARD_SIZE;
}

//int Logic::rowCount(const QModelIndex &) const
//{
//    return NUMBER_CELLS;
//}

//QHash<int, QByteArray> Logic::roleNames() const
//{
//    QHash<int, QByteArray> names;

//    names.insert(Roles::Number, "number");

//    return names;
//}

//QVariant Logic::data(const QModelIndex &modelIndex, int role) const
//{
//    if (!modelIndex.isValid())
//        return QVariant();

//    int index = static_cast<int>(modelIndex.row());

//    if (index >= NUMBER_CELLS || index < 0)
//        return QVariant();

//    Cell &cell = cells[index];

//    switch (role) {
//        case Roles::Number: return cell.number;
//    }
//    return QVariant();
//}

void Logic::setStartCoordinates(void)
{
   cells[0] = 1;
   cells[1] = 2;
   cells[2] = 3;
   cells[3] = 4;
   cells[4] = 5;
   cells[5] = 6;
   cells[6] = 7;
   cells[7] = 8;
   cells[8] = 10;
   cells[9] = 11;
   cells[10] = 12;
   cells[11] = 15;
   cells[12] = 9;
   cells[13] = 13;
   cells[14] = 14;
   cells[15] = 0;
}

bool Logic::isTrueIndex(int index) const
{
    if (index >= 0 && index < NUMBER_CELLS)
        return true;
    else
        return false;
}

void Logic::move(int index)
{
//    int empty_num;
//    int index_empty_cell;

//    if (number < 1)
//        return ;

//    index_empty_cell = -1;
//    index = getIndexCell(fromX, fromY);

//    if (index == -1)
//        return ;

    int num;

    if (isTrueIndex(index - 4) && cells[index - 4] == NUM_EMPTY_CELL)
        cells[index - 4] = cells[index];
    else if (isTrueIndex(index + 4) && cells[index + 4] == NUM_EMPTY_CELL)
        cells[index + 4] = cells[index];
    else if (isTrueIndex(index - 1) && cells[index - 1] == NUM_EMPTY_CELL)
        cells[index - 1] = cells[index];
    else if (isTrueIndex(index + 1) && cells[index + 1] == NUM_EMPTY_CELL)
        cells[index + 1] = cells[index];
    else
        return ;

    cells[index] = NUM_EMPTY_CELL;

    QModelIndex topLeft = createIndex(0, 0);
    QModelIndex bottomRight = createIndex(NUMBER_CELLS - 1, 0);
    emit dataChanged(topLeft, bottomRight);
}

bool Logic::checkWin() const
{
    if (cells[NUMBER_CELLS - 1].number != NUM_EMPTY_CELL)
        return false;
    for (int i = 1; i < NUMBER_CELLS - 1; ++i)
        if (cells[i - 1].number != cells[i].number - 1)
            return false;
    return true;
}


