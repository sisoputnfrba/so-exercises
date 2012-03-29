/*
 * Ejercicio2.c
 *
 *  Created on: 10/03/2012
 *      Author: sebastian
 */

#include "Ejercicio2.h"

#define JOBQUEUESIZE 10
pthread_mutex_t mutexImpresion;//Para asegurar la mutua exclusion en la cola de trabajo
sem_t semImpresora;//Para que la impresora se suspenda si no tiene trabajos
sem_t semColaPC;//Para que las PC no manden mas de 10 trabajos
t_queue * jobQueue;
int main (void)
{
	pthread_t h1,h2,h3,h4;
	jobQueue =queue_create();
	pthread_mutex_init(&mutexImpresion,NULL);
	sem_init(&semImpresora,0,0);
	sem_init(&semColaPC,0,JOBQUEUESIZE);
	pthread_create(&h1,NULL,Trabajar,"PC-1");
	pthread_create(&h2,NULL,Trabajar,"PC-2");
	pthread_create(&h3,NULL,Trabajar,"PC-3");
	pthread_create(&h4,NULL,ProcesarColaImpresion,NULL);
	pthread_join(h1,(void**)NULL);
	pthread_join(h2,(void**)NULL);
	pthread_join(h3,(void**)NULL);
	pthread_join(h4,(void**)NULL);
	return EXIT_SUCCESS;
}

void * Trabajar(void * args)
{
	char* nombre=(char*) args;
	for(int i=0;i<10;i++)
	{
		MandarAImprimir(jobQueue , nombre);
		usleep(1);
	}

	return NULL;
}

void * ProcesarColaImpresion(void * args)
{

	t_print_job* job;
	while(true)
	{
		job=(t_print_job*)queue_sync_pop(jobQueue);
		printf("Imprimiendo trabajo de PC %s , datos a imprimir: %s\n",job->pc,job->data);
		usleep(500);

	}
	return NULL;
}

void MandarAImprimir(t_queue* jobQueue,const char* nombre)
{
	t_print_job * job = malloc(sizeof(t_print_job));
	job->data = CrearDataAImprimir();
	job->pc=nombre;
	printf("PC: %s Enviando a la cola de impresion %s\n",job->pc,job->data);
	queue_sync_push(jobQueue,job);
}


char * CrearDataAImprimir()
{
	  static const char alphanum[] =
			        "0123456789"
			        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			        "abcdefghijklmnopqrstuvwxyz";

	char* data=malloc(10);
	for (int i = 0; i < 9; ++i)
	       data[i] = alphanum[rand() % (sizeof(alphanum) - 1)];

	data[9] = '\0';

	return data;
}
/*
 *Creamos un wrapper (un TAD que le agrega funcionalidades a otro) para agregar los semaforos a la cola
 *Se podria haber modificado el TAD t_queue pero eso lo hubiera hecho menos mantenible ya que tendriamos
 *que tener 2 versiones de t_queue.
 *que El patron de diseño decorator usa esta tecnica como una de sus principales reglas de diseño
 */
void* queue_sync_pop(t_queue* self)
{
	sem_wait(&semImpresora);

	pthread_mutex_lock(&mutexImpresion);
	void* elem= queue_pop(self);
	pthread_mutex_unlock(&mutexImpresion);
	sem_post(&semColaPC);
	return elem;

}

void queue_sync_push(t_queue* self, void* element)
{
	sem_wait(&semColaPC);
	pthread_mutex_lock(&mutexImpresion);
	queue_push(self,element);
	pthread_mutex_unlock(&mutexImpresion);
	sem_post(&semImpresora);

}

