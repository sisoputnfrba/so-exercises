/*
 * Mascota.c
 *
 *  Created on: Apr 3, 2012
 *      Author: shinichi
 */


#include "Mascota.h"

#include <stdlib.h>
#include <string.h>

t_mascota* t_mascota_crear(char* apodo, bool daVueltas, int edad) {
	t_mascota* mascota = malloc(sizeof(t_mascota));
	mascota->apodo = strdup(apodo);
	mascota->daVueltas = daVueltas;
	mascota->edad = edad;

	return mascota;
}

void t_mascota_destroy(t_mascota* mascota) {
	free(mascota->apodo);
	free(mascota);
}
