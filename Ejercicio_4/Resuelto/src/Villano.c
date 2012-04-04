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

t_stream* t_villano_serialize(t_Villano* villano) {
	t_stream *stream = t_stream_create(sizeof(t_Villano));
	memcpy(stream->data, villano, sizeof(t_Villano));
	return stream;
}

t_Villano* t_villano_deserialize(char* stream, int* size) {
	t_Villano *villano = malloc(sizeof(t_Villano));
	memcpy(villano, stream, sizeof(t_Villano));

	*size = sizeof(t_Villano);

	return villano;
}
