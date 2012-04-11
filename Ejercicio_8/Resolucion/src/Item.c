/*
 * Item.c
 *
 *  Created on: Apr 10, 2012
 *      Author: shinichi
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
