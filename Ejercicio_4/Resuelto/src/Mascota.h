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

#ifndef MASCOTA_H_
#define MASCOTA_H_

#include <stdbool.h>
#include "Stream.h"

typedef struct {
	char* apodo;
	int edad;
	bool daVueltas;
}__attribute__((packed)) t_mascota;

t_mascota* t_mascota_crear(char* apodo, bool daVueltas, int edad);
void t_mascota_destroy(t_mascota* mascota);

t_stream* t_mascota_serialize(t_mascota* mascota);
t_mascota* t_mascota_deserialize(char* stream, int* size);

#endif /* MASCOTA_H_ */
