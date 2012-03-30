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
#include <unistd.h>
#include "Collections/queue.h"
void * Trabajar(void * args);
void * ProcesarColaImpresion(void * args);
void MandarAImprimir(t_queue* jobQueue);
char * CrearDataAImprimir();

typedef struct {

	int pc; //PC que hizo el pedido de impresion
	char* data; //Datos a imprimir

} t_print_job;
#endif /* EJERCICIO2_H_ */
