#ifndef AI_H
#define AI_H
#include "player.h"
#include<thread>
#include<QThreadPool>

class AI:public Player
{
    QVector<std::thread*> threads;
    int* movesVal = new int[100];// 100 - max amount
    Q_OBJECT
public:
    int depthValue=6;

    AI(bool isWhite):Player(isWhite,true){}
    ~AI(){}
     virtual void FindMove( Field& field,QList<Move>&moves) override;
    int minimax(Field& field,bool isBlack,int depth);
    void calculate(Move m,int&res, Field field,bool isWhite);

     public slots:
     virtual void clicked(int x, int y) override;
};

#endif // AI_H
