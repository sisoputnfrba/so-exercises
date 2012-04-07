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

#ifndef EJERCICIO3_H_
#define EJERCICIO3_H_

#include "Collections/queue.h"

typedef struct {
	bool embalada;
	t_queue* ingredientes;
} t_hamburguesa;

typedef enum {
	PANINFERIOR,
	CONDIMENTOS,
	CARNE,
	QUESO,
	PANCETA,
	LECHUGA,
	TOMATE,
	PANSUPERIOR,
} t_Ingredientes;

#endif /* EJERCICIO3_H_ */
