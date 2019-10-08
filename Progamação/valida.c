#include <stdio.h>
#include <stdlib.h>

typedef struct Pilha{

  char* vetor;
  int topo, max;

} Pilha;

Pilha* iniciarP(int size){
  Pilha *P = (Pilha*) malloc(sizeof(int)*2 + sizeof(char*));
  char *vetor = (char*) malloc(sizeof(char) * size);
  P->vetor = vetor;
  P->topo = -1;
  P->max = size;
  return P;
}

void adicionarP(Pilha *P, char x){
  if(P->topo == P->max - 1){
    printf("StackOverFlowException\n");
    exit(1);
  }
  P->vetor[++P->topo] = x;
}

char removerP(Pilha *P){
  if(P->topo == -1){
    printf("StackLowerFlowException\n");
    exit(1);
  }
  return P->vetor[P->topo--];
}

void printPilha(Pilha *P){
  printf("[");
  if(P->topo > -1) printf("%c", P->vetor[0]);
  for(int i=1; i<=P->topo; i++) printf(", %c", P->vetor[i]);
  printf("]\n");
}




int isNumber(char c){
  return c>='0' && c<='9';
}

int isOperator(char c){
  return c=='+' || c=='-' || c=='*' || c=='/';
}

int validar(char c, int caso){
  if(caso < 4) return c=='(' || isNumber(c);
  int boolean = c=='\0' || isOperator(c);
  if(caso == 4) return boolean;
  return boolean || c==')' || isNumber(c);
}

void printarInvalida(char* str, int i){
  printf("A expressão está inválida!\n");
  printf("%s\n", str);
  for(int i2=0; i2<i; i2++) printf("~");
  printf("%c\n", '^');
  exit(0);
}

void main(){
  // operador(O), número(N), abre('('), fecha(')'), fim(\0), inicio(I)
  // I --> N || abre              (1º caso)
  // O --> N || abre              (2º caso)
  // ( --> N || abre              (3º caso)
  // ) --> O || \0                (4º caso)
  // N --> N || O || fecha || \0  (5º caso)
  // \0 <-- Todos abertos foram fechados (último caso)
  char *exp = "(1+2)*3";
  int n = 0;
  for(;exp[n++];);
  n--;
  Pilha *P = iniciarP(n+1);
  for(int i=0; exp[i]; i++) {
    adicionarP(P, exp[n-i-1]);
    printPilha(P);
  }
  adicionarP(P, exp[n-1]);
  printPilha(P);
  for(int i=0; i<n; i++){
    if(i==0) {
      if(!validar(removerP(P), 1)) printarInvalida(exp, i);
    }else{
      char c = removerP(P);
      switch(c){
        char c2;
        case '(':
          c2 = removerP(P);
          adicionarP(P, c2);
          if(!validar(c2, 3)) printarInvalida(exp, i);
          break;
        case ')':
          c2 = removerP(P);
          adicionarP(P, c2);
          if(!validar(c2, 4)) printarInvalida(exp, i);
        case '\0':
          break;
        default:
          break;
      }
    }
  }
}