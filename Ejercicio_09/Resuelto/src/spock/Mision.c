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
 
#include "Mision.h"

#include <stdlib.h>
#include <string.h>

t_mision* mision_crear(char* mensaje) {
	t_mision* mision = malloc(sizeof(t_mision));
	mision->info_codificada = strdup(mensaje);
	mision->longitud = strlen(mision->info_codificada);
	return mision;
}

void mision_destroy(t_mision* mision) {
	free(mision->info_codificada);
	free(mision);
}

t_stream* mision_serialize(t_mision* mision) {
	int offset = 0;
	t_stream *stream = stream_create(strlen(mision->info_codificada) + 1 + sizeof(mision->longitud));

	memcpy(stream->data + offset, mision->info_codificada, strlen(mision->info_codificada) + 1);
	offset += strlen(mision->info_codificada) + 1;

	memcpy(stream->data + offset, &mision->longitud, sizeof(mision->longitud));
	offset += sizeof(mision->longitud);

	return stream;
}

t_mision* mision_deserialize(char* stream, int* size) {
	t_mision* mision = malloc(sizeof(t_mision));
	int offset = 0;

	char* info = strdup(stream + offset);
	mision->info_codificada = info;
	offset += strlen(info) + 1;

	memcpy(&mision->longitud, stream + offset, sizeof(mision->longitud));
	offset += sizeof(mision->longitud);

	*size = offset;

	return mision;
}
