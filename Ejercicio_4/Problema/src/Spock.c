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

t_Spock* t_Spock_CrearSpock() {
	t_Spock* spock = malloc(sizeof(t_Spock));
	spock->edad = 40;
	spock->nombre = strdup("Roberto Spock");

	spock->mascota = t_mascota_crear("Babu", true, 5);
	spock->listaDeVillanos = list_create();

	list_add(spock->listaDeVillanos, t_villano_crear("Borg Queen", 34));
	list_add(spock->listaDeVillanos, t_villano_crear("Locotus", 20));
	list_add(spock->listaDeVillanos, t_villano_crear("Dukat", 67));

	char* mensaje = mensajeRandom();
	spock->mision = t_mision_crear(mensaje);

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

void t_Spock_EnviarAMision(t_Spock* spock) {
	FILE* file = fopen("./spock.bin", "w");
	fwrite(spock, sizeof(t_Spock), 1, file);
	fflush(file);
	fclose(file);
}

t_Spock* t_Spock_VolverDeMision() {
	printf("ahhhhhhh!! no podemos recuperar a Spock\n");
	return NULL;
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
