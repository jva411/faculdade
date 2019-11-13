#ifndef Already_Circulo
#define Already_Circulo 1
#include <stdlib.h>
#include <stdio.h>
#include "Ponto.c"
typedef struct Circulo Circulo;
Circulo *CirculoInitPPontoFloat(Ponto *, float);
struct Circulo{
    Ponto *centro;
    float raio;
};
Circulo *CirculoInitPPontoFloat(Ponto *centro, float raio){
    Circulo *this = (Circulo*) malloc(sizeof(Circulo));
    this->centro = centro;
    this->raio = raio;
    return this;
}
#endif