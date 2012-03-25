/*
 * Ejercicio2.h
 *
 *  Created on: 10/03/2012
 *      Author: sebastian
 */

#ifndef EJERCICIO2_H_
#define EJERCICIO2_H_
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
#include <sys/types.h>
#include <unistd.h>
#include "Collections/queue.h"
#include <semaphore.h>
void * Trabajar(void * args);
void * ProcesarColaImpresion(void * args);
void MandarAImprimir(t_queue* jobQueue,const char* nombre);
char * CrearDataAImprimir();
void* queue_sync_pop(t_queue* self);
void queue_sync_push(t_queue* self, void* element);
typedef struct {

	const char* pc; //PC que hizo el pedido de impresion
	char* data;

} t_print_job;


#endif /* EJERCICIO2_H_ */
