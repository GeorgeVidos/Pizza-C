#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

int Ncooks = 2;//diathesimoi chef
int Novens = 5; //diathesimoi fournoi
int Ndeliverer=10;
int Torderlow=1;
int Torderhigh=5;
int Norderlow=1;//pizzas
int Norderhigh=5;//pizzas
int Tprep=1;
int Tbake=10;
int Tlow=5 ;//lepta
int Thigh=15; //lepta



int maxTime=0;
int avgTime=0;
int avgTimeCold=0;
int maxCold=0;


int Ncust;

int seed;

