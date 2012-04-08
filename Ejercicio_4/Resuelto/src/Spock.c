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

t_spock* spock_crear() {
	t_spock* spock = malloc(sizeof(t_spock));
	spock->edad = 40;
	spock->nombre = strdup("Roberto Spock");

	spock->mascota = mascota_crear("Babu", true, 5);
	spock->villanos = list_create();

	list_add(spock->villanos, villano_crear("Borg Queen", 34));
	list_add(spock->villanos, villano_crear("Locotus", 20));
	list_add(spock->villanos, villano_crear("Dukat", 67));

	spock->mision = mision_crear(mensajeRandom());

	return spock;
}

void spock_destroy(t_spock* spock) {
	if (spock != NULL) {
		free(spock->nombre);
		mascota_destroy(spock->mascota);
		mision_destroy(spock->mision);
		list_destroy_and_destroy_elements(spock->villanos, (void*) villano_destroy);
		free(spock);
	}
}

t_stream* spock_serialize(t_spock* spock) {
	int offset = 0;
	t_stream* stream_spock = stream_create(sizeof(spock->edad) + strlen(spock->nombre) + 1);

	memcpy(stream_spock->data + offset, &spock->edad, sizeof(spock->edad));
	offset += sizeof(spock->edad);

	memcpy(stream_spock->data + offset, spock->nombre, strlen(spock->nombre) + 1);
	offset += strlen(spock->nombre) + 1;

	t_stream* stream_mascota = mascota_serialize(spock->mascota);
	stream_spock->data = realloc(stream_spock->data, stream_spock->size + stream_mascota->size);
	memcpy(stream_spock->data + offset, stream_mascota->data, stream_mascota->size);
	stream_spock->size += stream_mascota->size;
	offset += stream_mascota->size;
	stream_destroy(stream_mascota);

	t_stream* stream_mision = mision_serialize(spock->mision);
	stream_spock->data = realloc(stream_spock->data, stream_spock->size + stream_mision->size);
	memcpy(stream_spock->data + offset, stream_mision->data, stream_mision->size);
	stream_spock->size += stream_mision->size;
	offset += stream_mision->size;
	stream_destroy(stream_mision);

	void serialize_element_villano(void* element) {
		t_villano* villano = element;

		t_stream* stream_villano = villano_serialize(villano);
		stream_spock->data = realloc(stream_spock->data, stream_spock->size + stream_villano->size);
		memcpy(stream_spock->data + offset, stream_villano->data, stream_villano->size);
		stream_spock->size += stream_villano->size;
		offset += stream_villano->size;
		stream_destroy(stream_villano);
	}

	uint32_t count_villanos = list_size(spock->villanos);
	stream_spock->data = realloc(stream_spock->data, stream_spock->size + sizeof(count_villanos));
	memcpy(stream_spock->data + offset, &count_villanos, sizeof(count_villanos));
	stream_spock->size += sizeof(count_villanos);
	offset += sizeof(count_villanos);

	list_iterate(spock->villanos, serialize_element_villano);

	return stream_spock;
}

t_spock* spock_deserialize(char* stream, int* size) {
	t_spock* spock = malloc(sizeof(t_spock));
	int offset = 0, tmp_size = 0, i = 0;

	memcpy(&spock->edad, stream + offset, tmp_size = sizeof(spock->edad));
	offset += tmp_size;

	spock->nombre = strdup(stream + offset);
	offset += strlen(spock->nombre) + 1;

	spock->mascota = mascota_deserialize(stream + offset, &tmp_size);
	offset += tmp_size;

	spock->mision = mision_deserialize(stream + offset, &tmp_size);
	offset += tmp_size;

	int elements_villano = 0;
	memcpy(&elements_villano, stream + offset, sizeof(elements_villano));
	offset += sizeof(elements_villano);

	t_list* villanos = list_create();
	for (i = 0; i < elements_villano; ++i) {
		t_villano* villano = villano_deserialize(stream + offset, &tmp_size);
		offset += tmp_size;
		list_add(villanos, villano);
	}
	spock->villanos = villanos;

	*size = offset;

	return spock;
}

void spock_enviar_a_mision(t_spock* spock) {
	t_stream* stream_spock_write = spock_serialize(spock);

	FILE* file = fopen("./spock.bin", "w");
	fwrite(stream_spock_write->data, stream_spock_write->size, 1, file);
	fflush(file);
	fclose(file);

	stream_destroy(stream_spock_write);
}

t_spock* spock_volver_de_mision() {
	struct stat statSpock;
	stat("./spock.bin", &statSpock);

	FILE* file = fopen("./spock.bin", "r");
	t_stream* stream_spock_read = stream_create(statSpock.st_size);
	fread(stream_spock_read->data, statSpock.st_size, 1, file);
	fclose(file);
    t_spock *spock = spock_deserialize(stream_spock_read->data, &stream_spock_read->size);
    stream_destroy(stream_spock_read);

    return spock;
}

void spock_es_igual(t_spock* spock, t_spock* otro_spock) {
	assert(strcmp(spock->nombre, otro_spock->nombre) == 0);
	assert(spock->edad == otro_spock->edad);

	assert(strcmp(spock->mascota->apodo, otro_spock->mascota->apodo) == 0);

	assert(spock->mascota->da_vueltas == otro_spock->mascota->da_vueltas);

	assert(spock->mascota->edad == otro_spock->mascota->edad);

	assert(strcmp(spock->mision->informacionCodificada, otro_spock->mision->informacionCodificada) == 0);

	assert(spock->mision->longitudInformacionCodificada == otro_spock->mision->longitudInformacionCodificada);

	int i;
	for (i = 0; i < list_size(spock->villanos); ++i) {
		t_villano* villano_enviado = list_get(spock->villanos, i);
		t_villano* villano_recibido = list_get(spock->villanos, i);

		assert(strcmp(villano_enviado->nombre, villano_recibido->nombre) == 0);
		assert(villano_enviado->edad == villano_recibido->edad);
	}

}

void spock_print(t_spock* spock) {
	printf("Nombre: %s\n", spock->nombre);
	printf("Edad: %d\n", spock->edad);
	printf("Apodo de la mascota: %s\n", spock->mascota->apodo);
	printf("Mascota da vueltas?: %s\n", spock->mascota->da_vueltas ? "Si" : "No");
	printf("Edad de la mascota: %d\n", spock->mascota->edad);
	printf("Info Codificada: %s\n", spock->mision->informacionCodificada);
	printf("Longitud Info Codificada: %d\n", spock->mision->longitudInformacionCodificada);

	int i;
	printf("Villanos:\n");
	for (i = 0; i < list_size(spock->villanos); ++i) {
		t_villano* villano = list_get(spock->villanos, i);
		printf("Nombre Villano: %s\n", villano->nombre);
		printf("Edad del villano: %d\n", villano->edad);
	}

}

static char* mensajeRandom() {
	return "ABCDEFGHI";
}
