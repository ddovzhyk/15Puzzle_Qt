#ifndef LOGIC_H
#define LOGIC_H

#include <QAbstractListModel>
#include <QVector>

class Logic: public QAbstractListModel
{
   Q_OBJECT

public:
    enum GlobalConstants {
        BOARD_SIZE = 4,
        NUMBER_CELLS = 16,
        NUM_EMPTY_CELL = 0,
    };

    enum Roles {
        Number,
        PositionX,
        PositionY,
    };

    struct Cell
    {
        int number;
        int x;
        int y;
    };

public:
    explicit Logic(QObject *parent = 0);
    ~Logic();

    Q_PROPERTY(int boardSize READ boardSize CONSTANT)
    Q_PROPERTY(int numberCells READ numberCells CONSTANT)
    int boardSize() const;
    int numberCells() const;

    void setStartCoordinates(void);
    bool isEmptyCell(int x, int y) const;
    bool isCorrectCoordinates(int x, int y) const;
    int getIndexCell(int x, int y) const;
    Q_INVOKABLE void move(int number, int fromX, int fromY);
    Q_INVOKABLE bool checkWin(void) const;


protected:
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &modelIndex, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    QVector<Cell> cells;
};

#endif