/*
 * Mascota.h
 *
 *  Created on: Apr 3, 2012
 *      Author: shinichi
 */

#ifndef MASCOTA_H_
#define MASCOTA_H_

#include <stdbool.h>
#include "Stream.h"

typedef struct {
	char* apodo;
	int edad;
	bool daVueltas;
}__attribute__((packed)) t_mascota;

t_mascota* t_mascota_crear(char* apodo, bool daVueltas, int edad);
void t_mascota_destroy(t_mascota* mascota);

t_stream* t_mascota_serialize(t_mascota* mascota);
t_mascota* t_mascota_deserialize(char* stream, int* size);

#endif /* MASCOTA_H_ */
