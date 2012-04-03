/*
 * SolucionLeo.h
 *
 *  Created on: 07/03/2012
 *      Author: sebastian
 */

#ifndef SOLUCIONLEO_H_
#define SOLUCIONLEO_H_
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

void* ComprasMensuales(void * args);
int ConsultaSaldo();
void HacerCompras(int monto,const char* nombre);
void Comprar(int monto);


#endif /* SOLUCIONLEO_H_ */
