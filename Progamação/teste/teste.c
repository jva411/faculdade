/*
class Ponto{
    float x, y;

    Ponto(float x, float y){
        this.x = x;
        this.y = y;
    }

    Ponto soma(Ponto p2){
        Ponto p = new Ponto(0, 0);
        p.x = this.x + p2.x;
        p.y = this.y + p2.y;
        return p;
    }
}

class Circulo{
    Ponto centro;
    float raio;

    Circulo(Ponto centro, float raio){
        this.centro = centro;
        this.raio = raio;
    }
}

void main(){
    Ponto p1 = new Ponto(2, 2);
    Ponto p2 = new Ponto(3, 4);
    Ponto p3 = p1.soma(p2);
    printf("%f %f\n", p3.x, p3.y);
    Circulo c = new Circulo(p3, 4);
}
*/

#include <stdlib.h>
#include <stdio.h>
#include "Ponto.c"
#include "Circulo.c"



int main(){
    Ponto *p1 = PontoInitFloatFloat(2, 2);
    Ponto *p2 = PontoInitFloatFloat(3, 4);
    Ponto *p3 = Ponto_somaPPonto(p1, p2);
    printf("%f %f\n", p3->x, p3->y);
    Circulo *c = CirculoInitPPontoFloat(p3, 4);
}