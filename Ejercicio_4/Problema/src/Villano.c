/*
 * Villano.c
 *
 *  Created on: Apr 3, 2012
 *      Author: shinichi
 */


#include "Villano.h"

#include <stdlib.h>
#include <string.h>

t_Villano* t_villano_crear(char* nombre, int edad) {
	t_Villano* villano = malloc(sizeof(t_Villano));
	strncpy(villano->nombre, nombre, 24);
	villano->edad = edad;
	return villano;
}

void t_villano_destroy(t_Villano* villano) {
	free(villano);
}
