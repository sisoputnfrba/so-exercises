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
