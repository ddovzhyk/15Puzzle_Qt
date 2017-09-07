#include "logic.h"

Logic::Logic(QObject *parent)
    : QAbstractListModel(parent)
{
    for (int i = 0; i < NUMBER_CELLS; ++i)
        cells << Cell();
    setStartCoordinates();
}

Logic::~Logic()
{
    cells.clear();
}

int Logic::boardSize() const
{
    return BOARD_SIZE;
}

int Logic::numberCells() const
{
    return NUMBER_CELLS;
}

int Logic::rowCount(const QModelIndex &) const
{
    return cells.size();
}

QHash<int, QByteArray> Logic::roleNames() const
{
    QHash<int, QByteArray> names;

    names.insert(Roles::Number, "number");
    names.insert(Roles::PositionX, "positionX");
    names.insert(Roles::PositionY, "positionY");

    return names;
}

QVariant Logic::data(const QModelIndex &modelIndex, int role) const
{
    if (!modelIndex.isValid())
        return QVariant();

    int index = static_cast<int>(modelIndex.row());

    if (index >= cells.size() || index < 0)
        return QVariant();

    Cell cell = cells[index];

    switch (role) {
        case Roles::Number: return cell.number;
        case Roles::PositionX: return cell.x;
        case Roles::PositionY: return cell.y;
    }
    return QVariant();
}

void Logic::setStartCoordinates(void)
{
   cells[0] = Cell { 1, 0, 0 };
   cells[1] = Cell { 2, 1, 0 };
   cells[2] = Cell { 3, 2, 0 };
   cells[3] = Cell { 4, 3, 0 };
   cells[4] = Cell { 5, 0, 1 };
   cells[5] = Cell { 6, 1, 1 };
   cells[6] = Cell { 7, 2, 1 };
   cells[7] = Cell { 8, 3, 1 };
   cells[8] = Cell { 10, 0, 2 };
   cells[9] = Cell { 11, 1, 2 };
   cells[10] = Cell { 12, 2, 2 };
   cells[11] = Cell { 15, 3, 2 };
   cells[12] = Cell { 9, 0, 3 };
   cells[13] = Cell { 13, 1, 3 };
   cells[14] = Cell { 14, 2, 3 };
   cells[15] = Cell { 0, 3, 3 };
}

bool Logic::isEmptyCell(int x, int y) const
{
    int index;

    index = getIndexCell(x, y);
    if (cells[index].number == NUM_EMPTY_CELL)
        return true;
    return false;
}

bool Logic::isCorrectCoordinates(int x, int y) const
{
    if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE)
        return true;
    return false;
}

int Logic::getIndexCell(int x, int y) const
{
    for (int i = 0; i < NUMBER_CELLS; ++i)
        if (cells[i].x == x && cells[i].y == y)
            return i;
    return -1;
}

void Logic::move(int number, int fromX, int fromY)
{
    int index;
    int empty_num;
    int index_empty_cell;

    if (number < 1)
        return ;

    index_empty_cell = -1;
    index = getIndexCell(fromX, fromY);

    if (index == -1)
        return ;

    if (isCorrectCoordinates(fromX - 1, fromY) &&
                isEmptyCell(fromX - 1, fromY))
        index_empty_cell = getIndexCell(fromX - 1, fromY);
    else if (isCorrectCoordinates(fromX, fromY - 1) &&
                isEmptyCell(fromX, fromY - 1))
        index_empty_cell = getIndexCell(fromX, fromY - 1);
    else if (isCorrectCoordinates(fromX + 1, fromY) &&
                isEmptyCell(fromX + 1, fromY))
        index_empty_cell = getIndexCell(fromX + 1, fromY);
    else if (isCorrectCoordinates(fromX, fromY + 1) &&
                isEmptyCell(fromX, fromY + 1))
        index_empty_cell = getIndexCell(fromX, fromY + 1);
    else
        return ;

    if (index_empty_cell == -1)
        return ;

    empty_num = cells[index_empty_cell].number;
    cells[index_empty_cell].number = cells[index].number;
    cells[index].number = empty_num;

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


