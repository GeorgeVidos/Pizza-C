#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

int Ncooks = 6;//diathesimoi chef
int Novens = 6; //diathesimoi fournoi
int Torderlow=1;
int Torderhigh=5;
int Norderlow=1;//pizzas
int Norderhigh=5;//pizzas
int Tprep=1;
int Tbake=10;



int maxTime=0;
int avgTime=0;

int Ncust;

int seed;

