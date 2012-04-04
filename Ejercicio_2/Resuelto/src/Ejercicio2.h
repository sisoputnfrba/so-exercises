/*
 * Copyright (C) 2012 Sistemas Operativos - UTN FRBA. All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
