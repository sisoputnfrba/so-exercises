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

#include "Cliente.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define CLIENTE_NAME_MAX_LENGTH 256

t_cliente* cliente_create(char* nombre, char* apellido, int codigo_cliente) {
	t_cliente* cliente = malloc(sizeof(t_cliente));
	cliente->nombre = nombre;
	cliente->apellido = apellido;
	cliente->codigo_cliente = codigo_cliente;

	return cliente;
}

void cliente_destroy(t_cliente* cliente) {
	free(cliente);
}

t_cliente* cliente_from_file(FILE* file) {
	char nombre[CLIENTE_NAME_MAX_LENGTH];
	char apellido[CLIENTE_NAME_MAX_LENGTH];
	int codigo_cliente = 0;
	fscanf(file, "%d,%[^,],%s\n", &codigo_cliente, nombre, apellido);
	return cliente_create(nombre, apellido, codigo_cliente);
}
