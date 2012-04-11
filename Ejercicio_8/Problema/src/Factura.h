/*
 * Factura.h
 *
 *  Created on: Apr 10, 2012
 *      Author: shinichi
 */

#ifndef FACTURA_H_
#define FACTURA_H_

#include <stdio.h>

#include "Cliente.h"
#include "Collections/list.h"
#include "Item.h"

typedef enum {A, B, C} t_factura_tipo;

typedef struct {
	char numero;
	t_factura_tipo tipo;
	t_cliente* cliente;
	t_list* items;
	double total;
} t_factura;

t_factura* factura_crear(char numero, t_factura_tipo tipo, t_cliente* cliente, double total);
void factura_destroy(t_factura* factura);

void factura_add_item(t_factura* factura, t_item* item);
void factura_print(t_factura* factura);

t_factura* factura_from_file(FILE* file);

#endif /* FACTURA_H_ */
