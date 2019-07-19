#ifndef FIELD_H
#define FIELD_H
#include<QList>
#include"move.h"
#include<QDebug>
// 'b'-black 'd'-black damka
// 'w'-white' 'q'- white queen
// '-'-empty   'n'- none(no such cell);



class Field
{
public:
    Field();

   void draw();
   void change();
   char cells[4][8];
   char get(int x,int y){
       if(x>7 ||x<0||y<0|| y>7){
          return 'n';
       }
       if((x+y)%2==0) return 'n';
    x= x/2;
    return cells[x][y];
   }
   bool set(int x,int y,char value){
       if(x>7 ||x<0||y<0|| y>7){
          return false;
       }
    x= x/2;
     cells[x][y]=value;
    return true;
   }
   int countBlack(){
       int res=0;
       for(int i=0;i<4;i++)
           for(int j=0;j<8;j++)
               if(cells[i][j]=='b' ||cells[i][j]=='d')res+=1;
       return res;

   }
   int countWhite(){
       int res=0;
       for(int i=0;i<4;i++)
           for(int j=0;j<8;j++)
               if(cells[i][j]=='w' ||cells[i][j]=='q')res+=1;
       return res;
   }
    void show(){
        std::string a;
        qDebug()<<"+++++++++++++++++++";
        for(int i=7;i>=0;--i){
            a="";
            for(int j=0;j<8;++j)
                a+=get(j,i);
            qDebug()<<get(0,i)<<get(1,i)<<get(2,i)<<get(3,i)<<get(4,i)<<get(5,i)<<get(6,i)<<get(7,i);
        }

    }

   int selected[2];//?
   void resetGame();
   QList<Move>findMoves(int x,int y,bool isBlack=true,bool kill=true);
   QList<Move>findMoves(Move& m);
   QList<Move>findMoves(bool isBlack=true);
   void applyMove(Move&m);
   operator =(const Field& a){
       for(int i=0;i<4;i++)
           for(int j=0;j<8;j++)
               cells[i][j]=a.cells[i][j];
   }

};
#endif // FIELD_H
