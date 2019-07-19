#ifndef HUMAN_H
#define HUMAN_H
#include"player.h"

class Human: public Player
{
    Q_OBJECT
    QList<int*>clicked_cells;
public:
    Human(bool isWhite);
    virtual void FindMove(Field &field, QList<Move> &moves) override;
 public slots:
    virtual void clicked(int x, int y) override;
    void endTurn(Move x);
};

#endif // HUMAN_H
