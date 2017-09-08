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
        Number = Qt::UserRole
    };

public:
    explicit Logic(QObject *parent = 0);
    ~Logic();

    Q_PROPERTY(int boardSize READ getBoardSize CONSTANT)
    int getBoardSize() const;

    void setStartCoordinates();
    bool checkGame() const;
    bool isTrueIndex(int index) const;

    Q_INVOKABLE bool move(int index);
    Q_INVOKABLE bool checkWin() const;
    Q_INVOKABLE void newGame();

protected:
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &modelIndex, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    QVector<int> cells;
};

#endif
