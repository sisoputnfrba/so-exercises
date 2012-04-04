/*
 * Villano.h
 *
 *  Created on: Apr 3, 2012
 *      Author: shinichi
 */

#ifndef VILLANO_H_
#define VILLANO_H_

#include "Stream.h"

typedef struct {
	char nombre[25];
	int edad;
}__attribute__((packed)) t_Villano;

t_Villano* t_villano_crear(char* nombre, int edad);
void t_villano_destroy(t_Villano* villano);

t_stream* t_villano_serialize(t_Villano* villano);
t_Villano* t_villano_deserialize(char* stream, int* size);

#endif /* VILLANO_H_ */
