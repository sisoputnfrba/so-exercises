/*
 * Ejercicio3.h
 *
 *  Created on: 10/03/2012
 *      Author: sebastian
 */

#ifndef EJERCICIO3_H_
#define EJERCICIO3_H_
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include "Collections/queue.h"

typedef struct
{
	bool embalada;
	t_queue* ingredientes;
}t_hamburguesa;
typedef enum
{
	PANINFERIOR=0,
	CONDIMENTOS=1,
	CARNE=2,
	QUESO=3,
	PANCETA=4,
	LECHUGA=5,
	TOMATE=6,
	PANSUPERIOR=7,
	FIN=8

}t_Ingredientes;


void*  Agregar_Pan_Inferior (void * args);
void*  Agregar_Condimento (void * args);
void*  Agregar_Carne (void * args);
void*  Agregar_Queso (void * args);
void*  Agregar_Panceta (void * args);
void*  Agregar_Lechuga (void * args);
void*  Agregar_Tomate (void * args);
void*  Agregar_Pan_Superior (void * args);
void*  Entregar (void * args);
void Agregar(t_Ingredientes ingrediente);
char* Ingrediente_ToString(t_Ingredientes ingrediente);
int EstaBienArmada();
#endif /* EJERCICIO3_H_ */
