#ifndef Already_Ponto
#define Already_Ponto 1
#include <stdlib.h>
#include <stdio.h>
typedef struct Ponto Ponto;
Ponto *PontoInitFloatFloat(float, float);
Ponto *Ponto_somaPPonto(Ponto*, Ponto*);
struct Ponto{
    float x, y;
};
Ponto *PontoInitFloatFloat(float x, float y){
    Ponto *this = (Ponto*) malloc(sizeof(Ponto));
    this->x = x;
    this->y = y;
    return this;
}
Ponto *Ponto_somaPPonto(Ponto *this, Ponto *p2){
    Ponto *p = PontoInitFloatFloat(0, 0);
    p->x = this->x + p2->x;
    p->y = this->y + p2->y;
    return p;
}
#endif