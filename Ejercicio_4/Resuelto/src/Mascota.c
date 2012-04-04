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


t_stream* t_mascota_serialize(t_mascota* mascota) {
	int offset = 0;
	t_stream *stream = t_stream_create(sizeof (mascota->edad)
										+ sizeof (mascota->daVueltas)
										+ strlen(mascota->apodo) + 1);

	memcpy(stream->data + offset, &mascota->edad, sizeof(mascota->edad));
	offset += sizeof(mascota->edad);

	memcpy(stream->data + offset, &mascota->daVueltas, sizeof(mascota->daVueltas));
	offset += sizeof(mascota->daVueltas);

	memcpy(stream->data + offset, mascota->apodo, strlen(mascota->apodo) + 1);
	offset += strlen(mascota->apodo) + 1;

	return stream;
}

t_mascota* t_mascota_deserialize(char* stream, int* size) {
	t_mascota* mascota = malloc(sizeof(t_mascota));
	int offset = 0;

	memcpy(&mascota->edad, stream + offset, sizeof(mascota->edad));
	offset += sizeof(mascota->edad);

	memcpy(&mascota->daVueltas, stream + offset, sizeof(mascota->daVueltas));
	offset += sizeof(mascota->daVueltas);

	char* apodo = strdup(stream + offset);
	mascota->apodo = apodo;
	offset += strlen(apodo) + 1;

	*size = offset;

	return mascota;
}
