#include "ai.h"
#include"windows.h"
#include<QThread>
#include <iostream>
#include<QDebug>

void AI::calculate(Move m,int& res, Field field1,bool isWhite)
{
    field1.applyMove(m);
   res= ((m.becameGod?3:0) + m.gods_killed*2 + m.killed_num -minimax(field1,isWhite,1)); //!!isWhite=isWhite
 return;

}

void AI::FindMove( Field&field, QList<Move>& moves)
{
   Move res;
    if(moves.length()==1){giveMove(moves[0]);return;}
    threads.clear();
   int count = 0;
   for(Move m:moves){
       threads.push_back(new std::thread(calculate,this,m,std::ref(movesVal[count]),field,isWhite));
       count++;
   }
   for(int i=moves.length();i>0;i--){
       threads[i-1]->join();
       delete threads[i-1];
   }
   threads.clear();
   count=-100000;
    for(int i=moves.length()-1;i>=0;i--){
    //    qDebug()<<"from:"<< moves[i].ordes.first()[0]<<"," <<moves[i].ordes.first()[0] <<"to"<<moves[i].ordes[1][0]<< ","<< moves[i].ordes[1][1]<<'|'<<movesVal[i];
       if(count<movesVal[i] || ((rand()%2) && count==movesVal[i])){
            count=movesVal[i];
            res=moves[i];
       }
   }
  //qDebug()<<"-------------";
   giveMove(res);
}

int AI::minimax(Field &field,bool isBlack, int depth=0)
{
    if(depth>depthValue){
        return 0;
    }
    QList<Move>moves=field.findMoves(isBlack);
   int res=-100000;
   int temp;
 Field field1;
    for(Move& move:moves){
        field1=field;
        field1.applyMove(move);
        temp=(move.becameGod?3:0) + move.gods_killed*2 + move.killed_num-minimax(field1,!isBlack,depth+1);
        if(temp>res)res=temp;
    }
    if(res==-100000)res=-100;
    return res;
}

void AI::clicked(int x, int y)
{

}
