/*
 * Mascota.h
 *
 *  Created on: Apr 3, 2012
 *      Author: shinichi
 */

#ifndef MASCOTA_H_
#define MASCOTA_H_

#include <stdbool.h>

typedef struct {
	char* apodo;
	int edad;
	bool daVueltas;
}__attribute__((packed)) t_mascota;

t_mascota* t_mascota_crear(char* apodo, bool daVueltas, int edad);
void t_mascota_destroy(t_mascota* mascota);

#endif /* MASCOTA_H_ */
