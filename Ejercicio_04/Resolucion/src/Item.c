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

#include "Item.h"
#include <stdlib.h>
#include <stdio.h>

#define ITEM_NAME_MAX_LENGTH 256

t_item* item_create(char* nombre, double precio) {
	t_item* item = malloc(sizeof(t_item));
	item->nombre = nombre;
	item->precio = precio;
	return item;
}

void item_destroy(t_item* item) {
	free(item->nombre);
	free(item);
}

t_item* item_from_file(FILE* file) {
	double precio;
	char* nombre = malloc(ITEM_NAME_MAX_LENGTH);
	fscanf(file, "%[^,],%lf\n", nombre, &precio);
	return item_create(nombre, precio);
}
