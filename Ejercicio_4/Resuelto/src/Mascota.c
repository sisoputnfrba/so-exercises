/*
 * Copyright (C) 2012 Sistemas Operativos - UTN FRBA. All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
