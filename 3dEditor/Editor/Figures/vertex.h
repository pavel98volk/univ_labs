#ifndef VERTEX_H
#define VERTEX_H


class Vertex{
public:
    float  position[3];
    float  color[3];
    Vertex(){
    }
    Vertex(float x,float y,float z){
        position[0]=x;
        position[1]=y;
        position[2]=z;


    }
    void setColor(float r,float g,float b){
        color[0]=r;
        color[1]=g;
        color[2]=b;
    }
};

#endif // VERTEX_H
