#ifndef MOVE_H
#define MOVE_H
#include <vector>
#include <QList>

class Move{
public:
    QList<int*>ordes;
    int killed_num=0;
    int gods_killed=0;
    bool becameGod=false;
     Move(){

     }

     Move(const Move&a){
        this->copy(a);
     }

    void copy( const Move& a){
        killed_num=a.killed_num;
        gods_killed=a.gods_killed;
        becameGod=a.becameGod;
        for(int*c:ordes){
         delete c;
        }
        ordes.clear();
        for(int*c:a.ordes){
         ordes.push_back(new int[2]{c[0],c[1]});
        }
    }
    void operator =( const Move& a){
        killed_num=a.killed_num;
        gods_killed=a.gods_killed;
        becameGod=a.becameGod;
        for(int*c:ordes){
         delete c;
        }
        ordes.clear();
        for(int*c:a.ordes){
         ordes.push_back(new int[2]{c[0],c[1]});
        }
    }
    void clear(){
        for(int*a :ordes) delete a;
        ordes.clear();
        killed_num=-1;
    }
    int sign(int x){
        return x>0?1:-1;
    }

    bool wasKilled(int x,int y){
        int*prev=ordes.first();
        int*curr;
        for(int a=1;a<ordes.length();++a){
             curr=ordes[a];
          for(int i=1;i<abs(curr[0]-prev[0]);++i){
                if((prev[0]+i*sign(curr[0]-prev[0]))==x && (prev[1]+i*sign(curr[1]-prev[1]))==y){
                   return true;
                }
            }
          prev=curr;
        }
        return false;
    }

};


#endif // MOVE_H
