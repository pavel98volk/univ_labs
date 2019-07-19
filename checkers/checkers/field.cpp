#include "field.h"
#include<QDebug>

Field::Field()
{
resetGame();
}

void Field::resetGame(){
   for(int j=0;j<4;++j){
    for(int i=5;i<8;i++){
        cells[j][i]='w';
    }
    for(int i=3;i<5;i++){
     cells[j][i]='-';
    }
    for(int i=0;i<3;i++){
        cells[j][i]='b';
    }
   }
   return;
}

QList<Move> Field::findMoves(Move &m)
{
   char ch = get(m.ordes.first()[0],m.ordes.first()[1]);
   char x=m.ordes.last()[0],y=m.ordes.last()[1];
   int x1,y1;
   QList<Move> list;

   //maybe it is a queen already?
   if(ch=='b' && y==7) m.becameGod=true;
   if(ch=='w' && y==0) m.becameGod=true;


       //first we should check if we can kill other checked
       if(ch=='b' && !m.becameGod){
           if((get(x+1,y+1)=='w' ||get(x+1,y+1)=='q') &&(get(x+2,y+2)=='-') && !m.wasKilled(x+1,y+1)){
               Move move;
               move.copy(m);
               move.killed_num+=1;
               if(get(x+1,y+1)=='q')move.gods_killed+=1;
               move.ordes.push_back(new int[2]{x+2,y+2});//?
             list+= findMoves(move);
         }
         if((get(x-1,y+1)=='w' ||get(x-1,y+1)=='q') &&(get(x-2,y+2)=='-')&& !m.wasKilled(x-1,y+1)){

             Move move; move.copy(m);
             move.killed_num+=1;
             if(get(x-1,y+1)=='q')move.gods_killed+=1;
             move.ordes.push_back(new int[2]{x-2,y+2});//?
             list+= findMoves(move);
         }
         if((get(x+1,y-1)=='w' ||get(x+1,y-1)=='q') &&(get(x+2,y-2)=='-')&& !m.wasKilled(x+1,y-1)){
             Move move; move.copy(m);
             move.killed_num+=1;
             if(get(x+1,y-1)=='q')move.gods_killed+=1;
             move.ordes.push_back(new int[2]{x+2,y-2});//?
             list+= findMoves(move);
         }
         if((get(x-1,y-1)=='w' ||get(x-1,y-1)=='q') &&(get(x-2,y-2)=='-')&& !m.wasKilled(x-1,y-1)){

             Move move; move.copy(m);
             move.killed_num+=1;
             if(get(x-1,y-1)=='q')move.gods_killed+=1;
             move.ordes.push_back(new int[2]{x-2,y-2});//?
             list+= findMoves(move);
         }

       } else if(ch=='d'|| (ch=='b' && m.becameGod)){
            // need to checked if blocking was killed    like b-w-!w! can already be b-w-'-' and the move is available
           x1= x+1,y1=y+1;
            while(get(x1,y1)=='-' || m.wasKilled(x1,y1)){x1+=1;y1+=1;}
            if((get(x1,y1)=='w' ||get(x1,y1)=='q') &&(get(x1+1,y1+1)=='-' ||m.wasKilled(x1+1,y1+1))){
                x1+=1;y1+=1;
                 bool godKilled=(get(x1,y1)=='d')?true:false;
        while(get(x1,y1)=='-' || m.wasKilled(x1,y1)){
                Move move;
                move.copy(m);
                move.killed_num+=1;
                if(godKilled)move.gods_killed+=1;
                move.ordes.push_back(new int[2]{x1,y1});
                list+= findMoves(move);
                x1+=1;y1+=1;
                }
            }
            x1= x-1,y1=y+1;
            while(get(x1,y1)=='-' || m.wasKilled(x1,y1)){x1-=1;y1+=1;}
            if((get(x1,y1)=='w' ||get(x1,y1)=='q') &&(get(x1-1,y1+1)=='-'||m.wasKilled(x1-1,y1+1))){
                x1-=1;y1+=1;
                 bool godKilled=(get(x1,y1)=='d')?true:false;
                while(get(x1,y1)=='-' || m.wasKilled(x1,y1)){
                Move move;
                move.copy(m);
                move.killed_num+=1;
                if(godKilled)move.gods_killed+=1;
                move.ordes.push_back(new int[2]{x1,y1});
                list+= findMoves(move);
                x1-=1;y1+=1;
                }
            }
            x1= x+1,y1=y-1;
            while(get(x1,y1)=='-' || m.wasKilled(x1,y1)){x1+=1;y1-=1;}
            if((get(x1,y1)=='w' ||get(x1,y1)=='q') &&(get(x1+1,y1-1)=='-'||m.wasKilled(x1+1,y1-1))){
                x1+=1;y1-=1;
                 bool godKilled=(get(x1,y1)=='d')?true:false;
                while(get(x1,y1)=='-' || m.wasKilled(x1,y1)){
                Move move;
                move.copy(m);
                move.killed_num+=1;
                if(godKilled)move.gods_killed+=1;
                move.ordes.push_back(new int[2]{x1,y1});
                list+= findMoves(move);
                x1+=1;y1-=1;
                }
            }
            x1= x-1,y1=y-1;
            while(get(x1,y1)=='-' || m.wasKilled(x1,y1)){x1-=1;y1-=1;}
            if((get(x1,y1)=='w' ||get(x1,y1)=='q') &&(get(x1-1,y1-1)=='-'||m.wasKilled(x1-1,y1-1))){
                x1-=1;y1-=1;
                 bool godKilled=(get(x1,y1)=='d')?true:false;
                while(get(x1,y1)=='-' || m.wasKilled(x1,y1)){
                Move move;
                move.copy(m);
                move.killed_num+=1;
                if(godKilled)move.gods_killed+=1;
                move.ordes.push_back(new int[2]{x1,y1});
                list+= findMoves(move);
                x1-=1;y1-=1;
                }
           }


       }
        else if(ch=='w' && !m.becameGod){
         if((get(x+1,y+1)=='b' ||get(x+1,y+1)=='d') &&(get(x+2,y+2)=='-') && !m.wasKilled(x+1,y+1)){

             Move move; move.copy(m);
             move.killed_num+=1;
              if(get(x+1,y+1)=='d')move.gods_killed+=1;
             move.ordes.push_back(new int[2]{x+2,y+2});//?
             list+= findMoves(move);
         }
         if((get(x-1,y+1)=='b' ||get(x-1,y+1)=='d') &&(get(x-2,y+2)=='-') && !m.wasKilled(x-1,y+1)){

             Move move; move.copy(m);
             move.killed_num+=1;
              if(get(x-1,y+1)=='d')move.gods_killed+=1;
             move.ordes.push_back(new int[2]{x-2,y+2});//?
             list+= findMoves(move);
         }
         if((get(x+1,y-1)=='b' ||get(x+1,y-1)=='d') &&(get(x+2,y-2)=='-') && !m.wasKilled(x+1,y-1)){

             Move move; move.copy(m);
             move.killed_num+=1;
              if(get(x+1,y-1)=='d')move.gods_killed+=1;
             move.ordes.push_back(new int[2]{x+2,y-2});//?
             list+= findMoves(move);
         }
         if((get(x-1,y-1)=='b' ||get(x-1,y-1)=='d') &&(get(x-2,y-2)=='-') && !m.wasKilled(x-1,y-1)){

             Move move; move.copy(m);
             move.killed_num+=1;
             if(get(x-1,y-1)=='d')move.gods_killed+=1;
             move.ordes.push_back(new int[2]{x-2,y-2});//?
             list+= findMoves(move);
        }
       }else if(ch=='q' || (ch=='w' && m.becameGod)){
           x1= x+1,y1=y+1;
            while(get(x1,y1)=='-' || m.wasKilled(x1,y1)){x1+=1;y1+=1;}
            if((get(x1,y1)=='b' ||get(x1,y1)=='d') &&(get(x1+1,y1+1)=='-' ||m.wasKilled(x1+1,y1+1))){
                x1+=1;y1+=1;
                 bool godKilled=(get(x1,y1)=='d')?true:false;
                while(get(x1,y1)=='-' || m.wasKilled(x1,y1)){
                Move move;
                move.copy(m);
                move.killed_num+=1;
                 if(godKilled)move.gods_killed+=1;
                move.ordes.push_back(new int[2]{x1,y1});
                list+= findMoves(move);
                x1+=1;y1+=1;
                }
            }
            x1= x-1,y1=y+1;
            while(get(x1,y1)=='-' || m.wasKilled(x1,y1)){x1-=1;y1+=1;}
            if((get(x1,y1)=='b' ||get(x1,y1)=='d') &&(get(x1-1,y1+1)=='-'||m.wasKilled(x1-1,y1+1))){
                x1-=1;y1+=1;
                 bool godKilled=(get(x1,y1)=='d')?true:false;
                while(get(x1,y1)=='-' || m.wasKilled(x1,y1)){
                Move move;
                move.copy(m);
                move.killed_num+=1;
                if(godKilled)move.gods_killed+=1;
                move.ordes.push_back(new int[2]{x1,y1});
                list+= findMoves(move);
                x1-=1;y1+=1;
                }
            }
            x1= x+1,y1=y-1;
            while(get(x1,y1)=='-' || m.wasKilled(x1,y1)){x1+=1;y1-=1;}
            if((get(x1,y1)=='b' ||get(x1,y1)=='d') &&(get(x1+1,y1-1)=='-'||m.wasKilled(x1+1,y1-1))){
                x1+=1;y1-=1;
                 bool godKilled=(get(x1,y1)=='d')?true:false;
                while(get(x1,y1)=='-' || m.wasKilled(x1,y1)){
                Move move;
                move.copy(m);
                move.killed_num+=1;
                if(godKilled)move.gods_killed+=1;
                move.ordes.push_back(new int[2]{x1,y1});
                list+= findMoves(move);
                x1+=1;y1-=1;
                }
            }
            x1= x-1,y1=y-1;
            while(get(x1,y1)=='-' || m.wasKilled(x1,y1)){x1-=1;y1-=1;}
            if((get(x1,y1)=='b' ||get(x1,y1)=='d') &&(get(x1-1,y1-1)=='-'||m.wasKilled(x1-1,y1-1))){
                x1-=1;y1-=1;
                 bool godKilled=(get(x1,y1)=='d')?true:false;
                while(get(x1,y1)=='-' || m.wasKilled(x1,y1)){
                Move move;
                move.copy(m);
                move.killed_num+=1;
                if(godKilled)move.gods_killed+=1;
                move.ordes.push_back(new int[2]{x1,y1});
                list+= findMoves(move);
                x1-=1;y1-=1;
                }
           }
        }

   if(list.empty()){
       list.push_back(m);
     }

   return list;
}

QList<Move> Field::findMoves(bool isBlack){
    QList<Move> res;
    bool mustKill=false;
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if((i+j)%2){

                QList<Move> temp=findMoves(i,j,isBlack,mustKill);
                if(!mustKill){
                    for(Move&a:temp)if(a.killed_num)mustKill=true;

                    if(mustKill){
                        int count=0;
                        for(int a=0;a<res.length();)if(!(res[a].killed_num)){
                            res.removeAt(count);
                        } else count+=1;
                    }
                }
                res+=temp;

             }
           }
        }
    //test

    return res;
}

int sign(int x){
    return x>0?1:-1;
}
void Field::applyMove(Move &m)
{
    int*prev=m.ordes.first();
    char figure=this->get(prev[0],prev[1]);
    int*curr;
    this->set(prev[0],prev[1],'-');
    for(int a=1;a<m.ordes.length();++a){
         curr=m.ordes[a];
      for(int i=1;i<abs(curr[0]-prev[0]);++i){
            this->set((prev[0]+i*sign(curr[0]-prev[0])),(prev[1]+i*sign(curr[1]-prev[1])),'-');
        }
      prev=curr;
    }
    if(!m.becameGod)this->set(curr[0],curr[1],figure);
    else if(figure=='b')this->set(curr[0],curr[1],'d');
    else if(figure=='w')this->set(curr[0],curr[1],'q');
}


QList<Move> Field::findMoves(int x,int y,bool isBlack,bool kill){
    QList<Move> list;
    if(y==-1 || x==-1) return list;
    char ch=get(x,y);
    int x1,y1;
    if(isBlack){
        if((ch!='b') && (ch!='d')) return list;
        //first we should check if we can kill other checker

        if(ch=='b'){
            if((get(x+1,y+1)=='w' ||get(x+1,y+1)=='q') &&(get(x+2,y+2)=='-')){
                kill=true;
                Move move;
                move.killed_num=1;
                if(get(x+1,y+1)=='q')move.gods_killed=1;
                move.ordes.push_back(new int[2]{x,y});
                move.ordes.push_back(new int[2]{x+2,y+2});//?
              list+= findMoves(move);
          }
          if((get(x-1,y+1)=='w' ||get(x-1,y+1)=='q') &&(get(x-2,y+2)=='-')){
               kill=true;
              Move move;
              move.killed_num=1;
              if(get(x-1,y+1)=='q')move.gods_killed=1;
              move.ordes.push_back(new int[2]{x,y});
              move.ordes.push_back(new int[2]{x-2,y+2});//?
              list+= findMoves(move);
          }
          if((get(x+1,y-1)=='w' ||get(x+1,y-1)=='q') &&(get(x+2,y-2)=='-')){
               kill=true;
              Move move;
              move.killed_num=1;
              if(get(x+1,y-1)=='q')
                  move.gods_killed=1;
              move.ordes.push_back(new int[2]{x,y});
              move.ordes.push_back(new int[2]{x+2,y-2});//?
              list+= findMoves(move);
          }
          if((get(x-1,y-1)=='w' ||get(x-1,y-1)=='q') &&(get(x-2,y-2)=='-')){
              kill=true;
              Move move;
              move.killed_num=1;
              if(get(x-1,y-1)=='q')move.gods_killed=1;
              move.ordes.push_back(new int[2]{x,y});
              move.ordes.push_back(new int[2]{x-2,y-2});//?
              list+= findMoves(move);
          }
          if(!kill){
              if(get(x+1,y+1) =='-'){
                 Move move;
                 move.killed_num=0;
                 if((y+1)==7)move.becameGod=true;
                 move.ordes.push_back(new int[2]{x,y});
                 move.ordes.push_back(new int[2]{x+1,y+1});
                 list.append(move);
             }
             if(get(x-1,y+1)=='-'){

                 Move move;
                 move.killed_num=0;
                 if((y+1)==7)move.becameGod=true;
                 move.ordes.push_back(new int[2]{x,y});
                 move.ordes.push_back(new int[2]{x-1,y+1});
                  list.append(move);
             }
          }

        } else if(ch=='d'){
            x1= x+1,y1=y+1;
             while(get(x1,y1)=='-'){x1+=1;y1+=1;}
             if((get(x1,y1)=='w' ||get(x1,y1)=='q') &&(get(x1+1,y1+1)=='-')){
                 kill=true;
                 x1+=1;y1+=1;
                 bool godKilled=(get(x1,y1)=='q')?true:false;
                 while(get(x1,y1)=='-'){
                 Move move;
                 move.killed_num=1;
                 if(godKilled)move.gods_killed=1;
                 move.ordes.push_back(new int[2]{x,y});
                 move.ordes.push_back(new int[2]{x1,y1});
                 list+= findMoves(move);
                 x1+=1;y1+=1;
                 }
             }
             x1= x-1,y1=y+1;
             while(get(x1,y1)=='-'){x1-=1;y1+=1;}
             if((get(x1,y1)=='w' ||get(x1,y1)=='q') &&(get(x1-1,y1+1)=='-')){
                  kill=true;
                 x1-=1;y1+=1;
                 bool godKilled=(get(x1,y1)=='q')?true:false;
                 while(get(x1,y1)=='-'){
                 Move move;
                 move.killed_num=1;
                 if(godKilled)move.gods_killed=1;
                 move.ordes.push_back(new int[2]{x,y});
                 move.ordes.push_back(new int[2]{x1,y1});
                 list+= findMoves(move);
                 x1-=1;y1+=1;
                 }
             }
             x1= x+1,y1=y-1;
             while(get(x1,y1)=='-'){x1+=1;y1-=1;}
             if((get(x1,y1)=='w' ||get(x1,y1)=='q') &&(get(x1+1,y1-1)=='-')){
                  kill=true;
                 x1+=1;y1-=1;
                 bool godKilled=(get(x1,y1)=='q')?true:false;
                 while(get(x1,y1)=='-'){
                 Move move;
                 move.killed_num=1;
                 if(godKilled)move.gods_killed=1;
                 move.ordes.push_back(new int[2]{x,y});
                 move.ordes.push_back(new int[2]{x1,y1});
                 list+= findMoves(move);
                 x1+=1;y1-=1;
                 }
             }
             x1= x-1,y1=y-1;
             while(get(x1,y1)=='-'){x1-=1;y1-=1;}
             if((get(x1,y1)=='w' ||get(x1,y1)=='q') &&(get(x1-1,y1-1)=='-')){
                  kill=true;
                 x1-=1;y1-=1;
                  bool godKilled=(get(x1,y1)=='q')?true:false;
                 while(get(x1,y1)=='-'){
                 Move move;
                 move.killed_num=1;
                 if(godKilled)move.gods_killed=1;
                 move.ordes.push_back(new int[2]{x,y});
                 move.ordes.push_back(new int[2]{x1,y1});
                 list+= findMoves(move);
                 x1-=1;y1-=1;
                 }
             }
             if(!kill){
                 x1=x+1;y1=y+1;
                while(get(x1,y1) =='-'){
                    Move move;
                    move.killed_num=0;
                    move.ordes.push_back(new int[2]{x,y});
                    move.ordes.push_back(new int[2]{x1,y1});
                    list.append(move);
                    x1+=1;y1+=1;
                }
                x1=x-1;y1=y+1;
               while(get(x1,y1) =='-'){
                   Move move;
                   move.killed_num=0;
                   move.ordes.push_back(new int[2]{x,y});
                   move.ordes.push_back(new int[2]{x1,y1});
                    list.append(move);
                     x1-=1;y1+=1;
               }
               x1=x+1;y1=y-1;
              while(get(x1,y1) =='-'){
                  Move move;
                  move.killed_num=0;
                  move.ordes.push_back(new int[2]{x,y});
                  move.ordes.push_back(new int[2]{x1,y1});
                   list.append(move);
                    x1+=1;y1-=1;
              }
              x1=x-1;y1=y-1;
             while(get(x1,y1) =='-'){
                 Move move;
                 move.killed_num=0;
                 move.ordes.push_back(new int[2]{x,y});
                 move.ordes.push_back(new int[2]{x1,y1});
                  list.append(move);
                  x1-=1;y1-=1;
             }

             }
         }
    } else{
        if((ch!='w') && (ch!='q')) return list;
        if(ch=='w'){
          if((get(x+1,y+1)=='b' ||get(x+1,y+1)=='d') &&(get(x+2,y+2)=='-')){
               kill=true;
              Move move;
              move.killed_num=1;
              if(get(x+1,y+1)=='d')move.gods_killed=1;
              move.ordes.push_back(new int[2]{x,y});
              move.ordes.push_back(new int[2]{x+2,y+2});//?
              list+= findMoves(move);
          }
          if((get(x-1,y+1)=='b' ||get(x-1,y+1)=='d') &&(get(x-2,y+2)=='-')){
               kill=true;
              Move move;
              move.killed_num=1;
              if(get(x-1,y+1)=='d')move.gods_killed=1;
              move.ordes.push_back(new int[2]{x,y});
              move.ordes.push_back(new int[2]{x-2,y+2});//?
              list+= findMoves(move);
          }
          if((get(x+1,y-1)=='b' ||get(x+1,y-1)=='d') &&(get(x+2,y-2)=='-')){
               kill=true;
              Move move;
              move.killed_num=1;
              if(get(x+1,y-1)=='d')  move.gods_killed=1;

              move.ordes.push_back(new int[2]{x,y});
              move.ordes.push_back(new int[2]{x+2,y-2});//?
              list+= findMoves(move);
          }
          if((get(x-1,y-1)=='b' ||get(x-1,y-1)=='d') &&(get(x-2,y-2)=='-')){
              kill=true;
              Move move;
              move.killed_num=1;
              if(get(x-1,y-1)=='d') move.gods_killed=1;
              move.ordes.push_back(new int[2]{x,y});
              move.ordes.push_back(new int[2]{x-2,y-2});//?
              list+= findMoves(move);
          }
          if(!kill){
             if(get(x+1,y-1) =='-'){
                 Move move;
                 move.killed_num=0;
                 if((y-1)==0)move.becameGod=true;
                 move.ordes.push_back(new int[2]{x,y});
                 move.ordes.push_back(new int[2]{x+1,y-1});
                  list.append(move);

             }
             if(get(x-1,y-1) =='-'){
                 Move move;
                 move.killed_num=0;
                 if((y-1)==0)move.becameGod=true;
                 move.ordes.push_back(new int[2]{x,y});
                 move.ordes.push_back(new int[2]{x-1,y-1});
                  list.append(move);
             }
          }

        } else if(ch=='q'){
           x1= x+1,y1=y+1;
            while(get(x1,y1)=='-'){x1+=1;y1+=1;}
            if((get(x1,y1)=='b' ||get(x1,y1)=='d') &&(get(x1+1,y1+1)=='-')){
                kill=true;
                x1+=1;y1+=1;
                bool godKilled=(get(x1,y1)=='d')?true:false;
                while(get(x1,y1)=='-'){
                Move move;
                move.killed_num=1;
                if(godKilled)move.gods_killed=1;
                move.ordes.push_back(new int[2]{x,y});
                move.ordes.push_back(new int[2]{x1,y1});
                list+= findMoves(move);
                x1+=1;y1+=1;
                }
            }
            x1= x-1,y1=y+1;
            while(get(x1,y1)=='-'){x1-=1;y1+=1;}
            if((get(x-1,y+1)=='b' ||get(x1,y1)=='d') &&(get(x1-1,y1+1)=='-')){
                kill=true;
                x1-=1;y1+=1;
                bool godKilled=(get(x1,y1)=='d')?true:false;
                while(get(x1,y1)=='-'){
                Move move;
                move.killed_num=1;
                if(godKilled)move.gods_killed=1;
                move.ordes.push_back(new int[2]{x,y});
                move.ordes.push_back(new int[2]{x1,y1});
                list+= findMoves(move);
                x1-=1;y1+=1;
                }
            }
            x1= x+1,y1=y-1;
            while(get(x1,y1)=='-'){x1+=1;y1-=1;}
            if((get(x1,y1)=='b' ||get(x1,y1)=='d') &&(get(x1+1,y1-1)=='-')){
                kill=true;
                x1+=1;y1-=1;
                 bool godKilled=(get(x1,y1)=='d')?true:false;
                while(get(x1,y1)=='-'){
                Move move;
                move.killed_num=1;
               if(godKilled)move.gods_killed=1;
                move.ordes.push_back(new int[2]{x,y});
                move.ordes.push_back(new int[2]{x1,y1});
                list+= findMoves(move);
                x1+=1;y1-=1;
                }
            }
            x1= x-1,y1=y-1;
            while(get(x1,y1)=='-'){x1-=1;y1-=1;}
            if((get(x1,y1)=='b' ||get(x1,y1)=='d') &&(get(x1-1,y1-1)=='-')){
                kill=true;
                x1-=1;y1-=1;
                 bool godKilled=(get(x1,y1)=='d')?true:false;
                while(get(x1,y1)=='-'){
                Move move;
                move.killed_num=1;
                if(godKilled)move.gods_killed=1;
                move.ordes.push_back(new int[2]{x,y});
                move.ordes.push_back(new int[2]{x1,y1});
                list+= findMoves(move);
                x1-=1;y1-=1;
                }
            }
            if(!kill){
                x1=x+1;y1=y+1;
               while(get(x1,y1) =='-'){
                   Move move;
                   move.killed_num=0;
                   move.ordes.push_back(new int[2]{x,y});
                   move.ordes.push_back(new int[2]{x1,y1});
                   list.append(move);
                   x1+=1;y1+=1;
               }
               x1=x-1;y1=y+1;
              while(get(x1,y1) =='-'){
                  Move move;
                  move.killed_num=0;
                  move.ordes.push_back(new int[2]{x,y});
                  move.ordes.push_back(new int[2]{x1,y1});
                   list.append(move);
                    x1-=1;y1+=1;
              }
              x1=x+1;y1=y-1;
             while(get(x1,y1) =='-'){
                 Move move;
                 move.killed_num=0;
                 move.ordes.push_back(new int[2]{x,y});
                 move.ordes.push_back(new int[2]{x1,y1});
                  list.append(move);
                   x1+=1;y1-=1;
             }
             x1=x-1;y1=y-1;
            while(get(x1,y1) =='-'){
                Move move;
                move.killed_num=0;
                move.ordes.push_back(new int[2]{x,y});
                move.ordes.push_back(new int[2]{x1,y1});
                 list.append(move);
                 x1-=1;y1-=1;
            }

            }
        }
    }


    return list;
}
