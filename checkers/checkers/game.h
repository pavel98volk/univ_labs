#ifndef GAME_H
#define GAME_H
#include "field.h"
#include "move.h"
#include <QObject>
#include <vector>
#include <QKeyEvent>
#include <QMouseEvent>
#include "player.h"
#include "ai.h"
#include "human.h"
#include<Qlist>
#include <QLabel>
#include<QString>
#include<QCheckBox>
#include"windows.h"

#define WHITE_BOOL true
#define BLACK_BOOL false

#define BLACK_WIN 1
#define WHITE_WIN -1
#define DRAW 0
class Game: public QObject
{
    Q_OBJECT
public:
    Field field;
    bool turn;
    Player*white=nullptr;
    Player*black=nullptr;
    QList<Move> moves;//?
    int *circ_em = new int[2];
    QList<int*>cell_em;
    int blackCount=12;
    int whiteCount=12;
    QLabel* turn_UI;
    QLabel* blackCount_UI;
    QLabel* whiteCount_UI;
   Game(QObject*parent=nullptr);
   void start(bool whiteAI,bool blackAI);
   void restart();
   void reset();
   void draw();
   void changeTurn();

private:
   int sign(int x){
       return x>0?1:-1;
   }

  signals:
   click(int x,int y);
   drawField(QList<int*>& cells_em,Field& field,int* ch_em,int phantomx=-1,int phantomy=-1);
public slots:
  void endGame(int result);
  void makeMove(Move m);
  void clicked(int x,int y);
  void playerDraw( QList<int*>& cells_em,int* ch_em,int phantomx=-1,int phantomy=-1);
  void onMousePress(QMouseEvent *event);
  void onmMouseRelease(QMouseEvent *event);
  void onMouseMove(QMouseEvent *event);

};

#endif // GAME_H
