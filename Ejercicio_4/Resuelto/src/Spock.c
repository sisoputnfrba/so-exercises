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

#include "Spock.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <assert.h>

static char* mensajeRandom();

t_Spock* t_Spock_CrearSpock() {
	t_Spock* spock = malloc(sizeof(t_Spock));
	spock->edad = 40;
	spock->nombre = strdup("Roberto Spock");

	spock->mascota = t_mascota_crear("Babu", true, 5);
	spock->listaDeVillanos = list_create();

	list_add(spock->listaDeVillanos, t_villano_crear("Borg Queen", 34));
	list_add(spock->listaDeVillanos, t_villano_crear("Locotus", 20));
	list_add(spock->listaDeVillanos, t_villano_crear("Dukat", 67));

	spock->mision = t_mision_crear(mensajeRandom());

	return spock;
}

void t_Spock_Destruir(t_Spock* spock) {
	if (spock != NULL) {
		free(spock->nombre);
		t_mascota_destroy(spock->mascota);
		t_mision_destroy(spock->mision);
		list_destroy_and_destroy_elements(spock->listaDeVillanos, (void*) t_villano_destroy);
		free(spock);
	}
}

t_stream* t_Spock_Serialize(t_Spock* spock) {
	int offset = 0;
	t_stream* stream_spock = t_stream_create(sizeof(spock->edad) + strlen(spock->nombre) + 1);

	memcpy(stream_spock->data + offset, &spock->edad, sizeof(spock->edad));
	offset += sizeof(spock->edad);

	memcpy(stream_spock->data + offset, spock->nombre, strlen(spock->nombre) + 1);
	offset += strlen(spock->nombre) + 1;

	t_stream* stream_mascota = t_mascota_serialize(spock->mascota);
	stream_spock->data = realloc(stream_spock->data, stream_spock->size + stream_mascota->size);
	memcpy(stream_spock->data + offset, stream_mascota->data, stream_mascota->size);
	stream_spock->size += stream_mascota->size;
	offset += stream_mascota->size;
	t_stream_destroy(stream_mascota);

	t_stream* stream_mision = t_mision_serialize(spock->mision);
	stream_spock->data = realloc(stream_spock->data, stream_spock->size + stream_mision->size);
	memcpy(stream_spock->data + offset, stream_mision->data, stream_mision->size);
	stream_spock->size += stream_mision->size;
	offset += stream_mision->size;
	t_stream_destroy(stream_mision);

	void serialize_element_villano(void* element) {
		t_Villano* villano = element;

		t_stream* stream_villano = t_villano_serialize(villano);
		stream_spock->data = realloc(stream_spock->data, stream_spock->size + stream_villano->size);
		memcpy(stream_spock->data + offset, stream_villano->data, stream_villano->size);
		stream_spock->size += stream_villano->size;
		offset += stream_villano->size;
		t_stream_destroy(stream_villano);
	}

	int count_villanos = list_size(spock->listaDeVillanos);
	stream_spock->data = realloc(stream_spock->data, stream_spock->size + sizeof(count_villanos));
	memcpy(stream_spock->data + offset, &count_villanos, sizeof(count_villanos));
	stream_spock->size += sizeof(count_villanos);
	offset += sizeof(count_villanos);

	list_iterate(spock->listaDeVillanos, serialize_element_villano);

	return stream_spock;
}

t_Spock* t_Spock_deserialize(char* stream, int* size) {
	t_Spock* spock = malloc(sizeof(t_Spock));
	int offset = 0, tmp_size = 0, i = 0;

	memcpy(&spock->edad, stream + offset, tmp_size = sizeof(spock->edad));
	offset += tmp_size;

	spock->nombre = strdup(stream + offset);
	offset += strlen(spock->nombre) + 1;

	spock->mascota = t_mascota_deserialize(stream + offset, &tmp_size);
	offset += tmp_size;

	spock->mision = t_mision_deserialize(stream + offset, &tmp_size);
	offset += tmp_size;

	int elements_villano = 0;
	memcpy(&elements_villano, stream + offset, sizeof(elements_villano));
	offset += sizeof(elements_villano);

	t_list* villanos = list_create();
	for (i = 0; i < elements_villano; ++i) {
		t_Villano* villano = t_villano_deserialize(stream + offset, &tmp_size);
		offset += tmp_size;
		list_add(villanos, villano);
	}
	spock->listaDeVillanos = villanos;

	*size = offset;

	return spock;
}

void t_Spock_EnviarAMision(t_Spock* spock) {
	t_stream* stream_spock_write = t_Spock_Serialize(spock);

	FILE* file = fopen("./spock.bin", "w");
	fwrite(stream_spock_write->data, stream_spock_write->size, 1, file);
	fflush(file);
	fclose(file);

	t_stream_destroy(stream_spock_write);
}

t_Spock* t_Spock_VolverDeMision() {
	struct stat statSpock;
	stat("./spock.bin", &statSpock);

	FILE* file = fopen("./spock.bin", "r");
	t_stream* stream_spock_read = t_stream_create(statSpock.st_size);
	fread(stream_spock_read->data, statSpock.st_size, 1, file);
	fclose(file);
    t_Spock *spock = t_Spock_deserialize(stream_spock_read->data, &stream_spock_read->size);
    t_stream_destroy(stream_spock_read);

    return spock;
}

void t_Spock_son_iguales(t_Spock* spock, t_Spock* otro_spock) {
	assert(strcmp(spock->nombre, otro_spock->nombre) == 0);
	assert(spock->edad == otro_spock->edad);

	assert(strcmp(spock->mascota->apodo, otro_spock->mascota->apodo) == 0);

	assert(spock->mascota->daVueltas == otro_spock->mascota->daVueltas);

	assert(spock->mascota->edad == otro_spock->mascota->edad);

	assert(strcmp(spock->mision->informacionCodificada, otro_spock->mision->informacionCodificada) == 0);

	assert(spock->mision->longitudInformacionCodificada == otro_spock->mision->longitudInformacionCodificada);

	int i;
	for (i = 0; i < list_size(spock->listaDeVillanos); ++i) {
		t_Villano* villano_enviado = list_get(spock->listaDeVillanos, i);
		t_Villano* villano_recibido = list_get(spock->listaDeVillanos, i);

		assert(strcmp(villano_enviado->nombre, villano_recibido->nombre) == 0);
		assert(villano_enviado->edad == villano_recibido->edad);
	}

}

static char* mensajeRandom() {
	return "ABCDEFGHI";
}
