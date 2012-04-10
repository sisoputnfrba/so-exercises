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

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

static char* mensajeRandom();

t_spock* spock_create() {
	t_spock* spock = malloc(sizeof(t_spock));
	spock->edad = 40;
	spock->nombre = strdup("Roberto Spock");

	spock->mascota = mascota_crear("Babu", true, 5);
	spock->villanos = list_create();

	list_add(spock->villanos, villano_create("Borg Queen", 34));
	list_add(spock->villanos, villano_create("Locotus", 20));
	list_add(spock->villanos, villano_create("Dukat", 67));

	char* mensaje = mensajeRandom();
	spock->mision = mision_crear(mensaje);

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

void spock_enviar_a_mision(t_spock* spock, char* file_name) {
	FILE* file = fopen(file_name, "w");
	fwrite(spock, sizeof(t_spock), 1, file);
	fflush(file);
	fclose(file);
}

t_spock* spock_volver_de_mision(char* file_name) {
	printf("ahhhhhhh!! no podemos recuperar a Spock\n");
	return NULL;
}

void spock_es_igual(t_spock* spock, t_spock* otro_spock) {
	assert(strcmp(spock->nombre, otro_spock->nombre) == 0);
	assert(spock->edad == otro_spock->edad);

	assert(strcmp(spock->mascota->apodo, otro_spock->mascota->apodo) == 0);
	assert(spock->mascota->da_vueltas == otro_spock->mascota->da_vueltas);
	assert(spock->mascota->edad == otro_spock->mascota->edad);

	assert(strcmp(spock->mision->info_codificada, otro_spock->mision->info_codificada) == 0);
	assert(spock->mision->longitud_info == otro_spock->mision->longitud_info);

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
	printf("Info Codificada: %s\n", spock->mision->info_codificada);
	printf("Longitud Info Codificada: %d\n", spock->mision->longitud_info);

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
