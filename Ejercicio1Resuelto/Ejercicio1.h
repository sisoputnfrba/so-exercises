/*
 * Ejercicio1.h
 *
 *  Created on: 07/03/2012
 *      Author: sebastian
 */

#ifndef EJERCICIO1_H_
#define EJERCICIO1_H_
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#include <sys/types.h>
#include <unistd.h>
void* ComprasMensuales(void * args);
int ConsultaSaldo();
void HacerCompras(int monto,const char* nombre);
void Comprar(int monto);


#endif /* EJERCICIO1_H_ */
