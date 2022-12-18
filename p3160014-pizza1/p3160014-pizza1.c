#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include "p3160014-p3160251-pizza1.h"
#define NCUST 10

pthread_mutex_t lockCooks;
pthread_mutex_t lockOvens;
pthread_mutex_t lockStatistics;
pthread_cond_t  condCooks;
pthread_cond_t  condOvens;
int id[NCUST];


float avgTime1=0;

unsigned int rand1(int min, int max, unsigned int* s) {//gennitria random arithmon
    return (rand_r(s) % (max - min + 1)) + min;
}
void *order(void *x){

    int id = *(int *)x;//to id toy pelati
    int rc;




	int Pnumber = rand1(Norderlow,Norderhigh,&seed);//ramdom arithmos apo pizzes pou thelei o pelatis


	//mia gia tous chef
    rc = pthread_mutex_lock(&lockCooks);//lock ton chef
    while (Ncooks == 0) {//an den exei chef perimene
	//printf("H paraggelia %d, den brike diathesimo paraskevasti. Blocked...\n", id);
	rc = pthread_cond_wait(&condCooks, &lockCooks);
    }
	//printf("H paraggelia %d eksipiretitai giati brike paraskevasti.\n", id);
    Ncooks--;//afou o chef mageireuei -1
    rc = pthread_mutex_unlock(&lockCooks);
    long timer = time(NULL);
	int PrepPizza = Pnumber * Tprep;

    sleep(PrepPizza); //koimisou mexri na ftiakseis oles tis pitses toy kathe pelati
	Ncooks++;//afou teleiwse tin paraskeuh o ched +1
	pthread_cond_signal(&condCooks);
	rc = pthread_mutex_unlock(&lockCooks);

	//kai mia gia tous fournous
	rc = pthread_mutex_lock(&lockOvens);//lock ton fourno
    while (Novens == 0) {//an den exei fourno perimene
	//printf("H paraggelia %d, den brike diathesimo fourno. Blocked...\n", id);
	rc = pthread_cond_wait(&condOvens, &lockOvens);
    }
	//printf("H paraggelia %d eksipiretitai giati brike fourno.\n", id);
    Novens--;//afou eksipiretitai -1 foyrnos
    rc = pthread_mutex_unlock(&lockOvens);//unlock ton fourno

    sleep(Tbake); //koimisou mexri na ginei i pizza
	Novens++;//afou den ton douleuyome allo ton ksanabazoume +1 (oti einai diathesimos dld)
	pthread_cond_signal(&condOvens);


	//ipologismos tou total time  tou max time kai toy avg time
    long totaltime = (time(NULL)-timer);
    pthread_mutex_lock(&lockStatistics);
    avgTime = avgTime + totaltime;
    if(totaltime > maxTime)
        maxTime = totaltime;
    pthread_mutex_unlock(&lockStatistics);


    printf("H paraggelia %d eksipiretithike epitixos se %lu  \n", id, totaltime);

    pthread_exit(NULL);//termatismos nimaton
}


int main(int argc, char *argv[])  {

	if (argc != 3) {
		printf("ERROR: Number of parameters (%d) is wrong, exiting program!\n",argc);
		exit(-1);
	}

	Ncust = atoi(argv[1]);//arithmos pelaton
	seed = atoi(argv[2]);//o arithos toy seed


	if (Ncust < 0) {
		printf("ERROR: the number of threads to run should be a positive number. Current number given %d.\n", Ncust);
		exit(-1);
	}



    int rc;
    pthread_t threads[Ncust];


	//initialization ton mutex
	pthread_mutex_init(&lockCooks,NULL);
	pthread_mutex_init(&lockStatistics, NULL);
	pthread_mutex_init(&lockOvens,NULL);
	pthread_cond_init(&condCooks,NULL);
	pthread_cond_init(&condOvens,NULL);


	//create ta threads
    for (int i = 0; i < Ncust; i++) {
	id[i] = i+1;
	//printf("Main: creating thread %d\n", i+1);
    	rc = pthread_create(&threads[i], NULL, order, &id[i]);
	if(id != 0){//an id!=0 tote exoume paraggelia
		sleep(rand1(Torderlow, Torderhigh,&seed));
	}
		if(rc != 0) {
		printf("ERROR: return code from pthread_create() is %d\n", rc);
       	exit(-1);
		}
    }

	void * status;//stamataei ta threads ,an den to baloumr mporei na teleiwsei pa teras prin apo ta threads 
	for(int i=0;i<Ncust;i++) {
		rc = pthread_join(threads[i],&status);
	}
avgTime1=avgTime/Ncust;
	printf("Average Time is %f minutes \n",avgTime1);
printf("max Time is %d minutes \n",maxTime);





	//destruction oton mutex
    pthread_mutex_destroy(&lockCooks);
    pthread_cond_destroy(&condCooks);
    pthread_mutex_destroy(&lockOvens);
    pthread_cond_destroy(&condOvens);
	pthread_mutex_destroy(&lockStatistics);

    return 0;
}


