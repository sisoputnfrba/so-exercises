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
