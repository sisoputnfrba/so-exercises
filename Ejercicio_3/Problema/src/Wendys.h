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

#ifndef WENDYS_H_
#define WENDYS_H_

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include "Collections/queue.h"

typedef struct {
	bool embalada;
	t_queue* ingredientes;
} t_hamburguesa;

typedef enum {
	PANINFERIOR = 0,
	CONDIMENTOS = 1,
	CARNE = 2,
	QUESO = 3,
	PANCETA = 4,
	LECHUGA = 5,
	TOMATE = 6,
	PANSUPERIOR = 7,
	FIN = 8
} t_Ingredientes;

void  agregar_pan_inferior();
void  agregar_condimento();
void  agregar_carne();
void  agregar_queso();
void  agregar_panceta();
void  agregar_lechuga();
void  agregar_tomate();
void  agregar_pan_superior();
void  entregar();
void  agregar(t_Ingredientes ingrediente);
char* ingrediente_to_string(t_Ingredientes ingrediente);
bool  esta_bien_armada();

#endif /* WENDYS_H_ */
