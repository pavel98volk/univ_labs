#ifndef PLAYER_H
#define PLAYER_H
#include<QList>
#include<QObject>
#include"field.h"
#include"move.h"
class Player:public QObject
{
    Q_OBJECT
public:
    bool isAI,isWhite;
     Field* field=nullptr;
    int*circ_em=new int[2]{-1,-1};
    QList<Move>* moves=nullptr;
    QList<int*> curr_move;
    QList<int*> cell_em;
    bool active=false;
    Player(bool isWhite,bool isAI);
    ~Player();
    virtual void FindMove(Field &field, QList<Move>&moves)=0;
   signals:
     giveMove(Move a);
     responce( QList<int*>& cells_em, int* ch_em,int phantomx=-1,int phantomy=-1);// to draw on screen
public slots:
  virtual void clicked(int x, int y)=0;
};



#endif // PLAYER_H
