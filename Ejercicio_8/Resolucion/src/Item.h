/*
 * Item.h
 *
 *  Created on: Apr 10, 2012
 *      Author: shinichi
 */

#ifndef ITEM_H_
#define ITEM_H_

#include <stdio.h>

typedef struct {
	char* nombre;
	double precio;
} t_item;

t_item* item_create(char* nombre, double precio);

void item_destroy(t_item* item);

t_item* item_from_file(FILE* file);

#endif /* ITEM_H_ */
