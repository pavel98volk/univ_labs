#include "game.h"
#include<vector>



Game::Game(QObject* parent):QObject(parent)
{
    circ_em[0] = -1;
    circ_em[1] = -1;
}



void Game::start(bool whiteAI, bool blackAI)
{
    turn_UI = this->parent()->findChild<QLabel*>("turn");
    blackCount_UI = this->parent()->findChild<QLabel*>("blackCount");
   whiteCount_UI = this->parent()->findChild<QLabel*>("whiteCount");
    if(white) delete white;
    if(black) delete black;
    if(whiteAI) white=new AI(true);
    else white=new Human(true);
    if(blackAI) black= new AI(false);
    else black=new Human(false);
    //connect(this,click,white,clicked);
    //connect(this,click,black,clicked);
    connect(black,Player::responce,this,playerDraw);
    connect(white,Player::responce,this,playerDraw);
    connect(black,Player::giveMove,this,makeMove);
    connect(white,Player::giveMove,this,makeMove);
     reset();
      turn=WHITE_BOOL;
/*

      for(int i=0;i<8;i++)
          for(int j=0;j<8;j++)
            field.set(i,j,'-');

      field.set(3, 7, 'd');
      //field.set(4, 3, 'w');
      field.set(7, 4, 'w');
      field.set(7, 2, 'b');

       //field.set(7, 0, 'q');

     blackCount=field.countBlack();
     whiteCount=field.countWhite();
     if(whiteCount_UI)whiteCount_UI->setText(QString::number(whiteCount));
     if(blackCount_UI)blackCount_UI->setText(QString::number(blackCount));
*/
      moves=field.findMoves(false);
      white->FindMove(field,moves);
     // click(-1,-1);
     // drawField(cell_em,field,circ_em);

}

void Game::reset()
{
    circ_em[0]=-1;
    circ_em[1]=-1;
    cell_em.clear();
    moves.clear();
    blackCount=12;
    whiteCount=12;
    field.resetGame();
}

void Game::changeTurn()
{
   turn=!turn;
   moves.clear();
   moves=field.findMoves((turn==BLACK_BOOL?true:false));
   if(moves.empty()){
        turn=!turn;
       moves=field.findMoves((turn==BLACK_BOOL?true:false));
       if(moves.isEmpty()){
           endGame(DRAW);
           return;
       }

   }
     if(whiteCount_UI)whiteCount_UI->setText(QString::number(whiteCount));
     if(blackCount_UI)blackCount_UI->setText(QString::number(blackCount));
   if(turn==BLACK_BOOL){
       if(turn_UI)turn_UI->setText("black");
       black->FindMove(field,moves);
   }
   else{
        if(turn_UI)turn_UI->setText("white");
        white->FindMove(field,moves);
   }



}

void Game::restart()
{
  bool w_AI= (this->parent()->findChild<QCheckBox*>("whiteAI"))->isChecked();
  bool b_AI= (this->parent()->findChild<QCheckBox*>("blackAI"))->isChecked();
  start(w_AI,b_AI);
}

void Game::endGame(int result)
{
   if(result==DRAW){

       for(int j=0;j<4;j++)
           for(int i=0;i<8;i++){
               if((i+j)%2)field.cells[i][j]='w';
               else field.cells[j][i]='w';
           }
   } else {
       char c='-';
       if(result==WHITE_WIN){
           c='q';
      for(int j=0;j<4;j++)
       for(int i=0;i<8;i++)
           field.cells[j][i]='w';
   } else  if(result==BLACK_WIN){
           c='d';
       for(int j=0;j<4;j++)
        for(int i=0;i<8;i++)
            field.cells[j][i]='b';
   }
       //w
   field.cells[2][2]=c;
   field.cells[2][3]=c;
   field.cells[2][4]=c;
   field.cells[2][5]=c;
   field.cells[1][2]=c;
   field.cells[1][3]=c;
   field.cells[1][4]=c;
   field.cells[1][5]=c;




   }
     drawField(cell_em,field,circ_em);
 // reset();
}

void Game::makeMove(Move m)
{
  field.applyMove(m);
    drawField(cell_em,field,circ_em);
    if(turn==BLACK_BOOL)whiteCount-=m.killed_num;
    else blackCount-=m.killed_num;
    if(!whiteCount){
        endGame(BLACK_WIN);
        return;
    }
    else if(!blackCount){
         endGame(WHITE_WIN);
         return;
    }
    changeTurn();
}

void Game::clicked(int x, int y)
{
    if(turn==BLACK_BOOL)black->clicked(x,y);
    else white->clicked(x,y);

}

void Game::playerDraw( QList<int *> &cells_em, int *ch_em,int phantomx,int phantomy)
{
 drawField(cells_em,field,ch_em,phantomx,phantomy);
}

void Game::onMousePress(QMouseEvent *event)
{

}

void Game::onmMouseRelease(QMouseEvent *event)
{

}

void Game::onMouseMove(QMouseEvent *event)
{

}
