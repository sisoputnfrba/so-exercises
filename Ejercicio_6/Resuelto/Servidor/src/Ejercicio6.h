/*
 * Ejercicio5.h
 *
 *  Created on: 11/03/2012
 *      Author: sebastian
 */

#ifndef EJERCICIO5_H_
#define EJERCICIO5_H_

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <semaphore.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/select.h>
#include "Collections/queue.h"
#include <string.h>

void iniciar_conexion();

void queue_sync_push(t_queue *, void *element);
void *queue_sync_pop(t_queue *);

#endif /* EJERCICIO5_H_ */
