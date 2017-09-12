#include "logic.h"

Logic::Logic(QObject *parent)
    : QAbstractListModel(parent)
{
    cells.resize(NUMBER_CELLS);
    setStartCoordinates();
}

Logic::~Logic()
{
    cells.clear();
}

int Logic::getBoardSize() const
{
    return BOARD_SIZE;
}

int Logic::rowCount(const QModelIndex &) const
{
    return NUMBER_CELLS;
}

QHash<int, QByteArray> Logic::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[Number] = "number";

    return roles;
}

QVariant Logic::data(const QModelIndex &modelIndex, int role) const
{
    if (!modelIndex.isValid())
        return QVariant();

    int index = static_cast<int>(modelIndex.row());

    if (index >= NUMBER_CELLS || index < 0)
        return QVariant();

    if (role == Roles::Number)
        return cells[index];

    return QVariant();
}

void Logic::setStartCoordinates()
{
    int i;

    for (i = 0; i < NUMBER_CELLS - 1; ++i)
        cells[i] = i + 1;
    cells[i] = NUM_EMPTY_CELL;

}

void Logic::random_shuffle()
{
    qsrand(unsigned(time(NULL)));
    for (int i = 0; i < NUMBER_CELLS; ++i)
        qSwap(cells[i], cells[qrand() % NUMBER_CELLS]);
}

void Logic::newGame()
{
    do
        random_shuffle();
    while (!checkGame());

    emit dataChanged(createIndex(0, 0), createIndex(NUMBER_CELLS - 1, 0));
}

bool Logic::checkGame() const
{
    int inv;
    int row_empty_cell;

    inv = 0;
    for (int i = 0; i < NUMBER_CELLS - 1; ++i)
        for (int j = i + 1; j < NUMBER_CELLS; ++j)
            if (cells[i] != NUM_EMPTY_CELL && cells[j] != NUM_EMPTY_CELL &&
                    cells[i] > cells[j])
                ++inv;
    row_empty_cell = cells.indexOf(NUM_EMPTY_CELL) / 4 + 1;

    return ((inv + row_empty_cell) % 2 == 0);
}

bool Logic::isTrueIndex(int index) const
{
    return (index >= 0 && index < NUMBER_CELLS);
}

bool Logic::move(int index)
{

    if (isTrueIndex(index - 4) && cells[index - 4] == NUM_EMPTY_CELL)
    {
        qSwap(cells[index], cells[index - 4]);
        if (beginMoveRows(QModelIndex(), index - 4, index - 4, QModelIndex(), index + 1))
        {
            endMoveRows();
            if (beginMoveRows(QModelIndex(), index - 1, index - 1, QModelIndex(), index - 4))
                endMoveRows();
        }
    }
    else if (isTrueIndex(index + 4) && cells[index + 4] == NUM_EMPTY_CELL)
    {
        qSwap(cells[index], cells[index + 4]);
        if (beginMoveRows(QModelIndex(), index + 4, index + 4, QModelIndex(), index + 1))
        {
            endMoveRows();
            if (beginMoveRows(QModelIndex(), index, index, QModelIndex(), index + 5))
                endMoveRows();
        }
    }
    else if (isTrueIndex(index - 1) && cells[index - 1] == NUM_EMPTY_CELL)
    {
        qSwap(cells[index], cells[index - 1]);
        if (beginMoveRows(QModelIndex(), index, index, QModelIndex(), index - 1))
            endMoveRows();
    }
    else if (isTrueIndex(index + 1) && cells[index + 1] == NUM_EMPTY_CELL)
    {
        qSwap(cells[index], cells[index + 1]);
        if (beginMoveRows(QModelIndex(), index, index, QModelIndex(), index + 2))
            endMoveRows();
    }
    else
        return false;

    return true;
}

bool Logic::checkWin() const
{
    if (cells[NUMBER_CELLS - 1] != NUM_EMPTY_CELL)
        return false;
    for (int i = 1; i < NUMBER_CELLS - 1; ++i)
        if (cells[i - 1] != cells[i] - 1)
            return false;
    return true;
}


