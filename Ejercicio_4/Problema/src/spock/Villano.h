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

#ifndef VILLANO_H_
#define VILLANO_H_

#include <stdint.h>

typedef struct {
	char nombre[25];
	uint16_t edad;
}__attribute__((packed)) t_villano;

t_villano* villano_create(char* nombre, int edad);
void villano_destroy(t_villano* villano);

#endif /* VILLANO_H_ */
