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

#ifndef MISION_H_
#define MISION_H_

#include "Mision.h"
#include "Stream.h"

#include "stdint.h"

typedef struct {
	char* info_codificada;
	uint32_t longitud;
}__attribute__((packed)) t_mision;

t_mision* mision_crear(char* mensaje);
void mision_destroy(t_mision* mision);

t_stream* mision_serialize(t_mision* mision);
t_mision* mision_deserialize(char* stream, int* size);

#endif /* MISION_H_ */
