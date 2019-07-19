#include "human.h"
#include<qdebug.h>

Human::Human(bool isWhite):Player(isWhite,false)
{
}

void Human::FindMove( Field&field, QList<Move>& moves)
{
 this->field = (&field);
 this->moves = &moves;
   for(Move& a :moves){
       cell_em.push_back(new int[2]{a.ordes[0][0],a.ordes[0][1]});
   }
   this->responce(cell_em,circ_em);
  //clicked_cells.clear();
  //cell_em.clear();
 active = true;
}


 void Human::clicked(int x, int y)
{
    if(!active)return;
        if((x+y)%2){
        if(field->get(x,y)!='-'){
            for(int*i :clicked_cells) delete i;
            clicked_cells.clear();
            circ_em[0]=x;
            circ_em[1]=y;
        }
        clicked_cells.push_back(new int[2]{x,y});
        cell_em.clear();
        for(Move& a : *moves){
            bool isValid=true;
            if(a.ordes.length()<clicked_cells.length())isValid=false;
            else for(int t=0;(t<clicked_cells.length())&&isValid;t++){
                   if(!(a.ordes[t][0]==clicked_cells[t][0] &&a.ordes[t][1]==clicked_cells[t][1])){isValid=false;}
            }
            if(isValid){
                if(clicked_cells.length()==a.ordes.length()){
                 endTurn(a);
                 return;//we found move!
                } else{

                    cell_em.push_back(a.ordes[clicked_cells.length()]);
                }
            }
        }
        if(cell_em.empty()){
            for(int*i :clicked_cells) delete i;
            clicked_cells.clear();
            circ_em[0]=-1;
            circ_em[1]=-1;
            responce(cell_em,circ_em);
        } else
            responce(cell_em,circ_em,x,y);
        } else{
             cell_em.clear();
            for(int*i :clicked_cells) delete i;
            clicked_cells.clear();

            circ_em[0]=-1;
            circ_em[1]=-1;
            responce(cell_em,circ_em);

        }


 }

 void Human::endTurn(Move x)
 {
   active=false;
   for(int*i :clicked_cells) delete i;
   clicked_cells.clear();
   for(int*i :cell_em) delete i;
   cell_em.clear();
   circ_em[0]=-1;
   circ_em[1]=-1;

    giveMove(x);


 }
