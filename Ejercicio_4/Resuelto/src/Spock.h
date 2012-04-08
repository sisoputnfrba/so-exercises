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

#ifndef SPOCK_H_
#define SPOCK_H_

#include "Mision.h"
#include "Villano.h"
#include "Stream.h"
#include "Mascota.h"
#include "Collections/list.h"

typedef struct {
	char* nombre;
	char edad;
	t_list* villanos;
	t_mascota* mascota;
	t_mision* mision;
}__attribute__((packed)) t_spock;

t_spock* spock_crear();
void spock_destroy(t_spock* spock);

t_stream* spock_serialize(t_spock* spock);
t_spock* spock_deserialize(char* stream, int* size);


void spock_enviar_a_mision(t_spock* spock);
t_spock* spock_volver_de_mision();

void spock_es_igual(t_spock* spock, t_spock* otro_spock);
void spock_print(t_spock* spock);

#endif /* SPOCK_H_ */
