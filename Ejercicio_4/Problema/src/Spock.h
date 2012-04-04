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
#include "Mascota.h"
#include "Villano.h"
#include "Collections/list.h"

typedef struct {
	char* nombre;
	int edad;
	t_list* listaDeVillanos;
	t_mascota* mascota;
	t_mision* mision;
}__attribute__((packed)) t_Spock;

t_Spock* t_Spock_CrearSpock();
void t_Spock_Destruir(t_Spock* spock);

void t_Spock_EnviarAMision(t_Spock* spock);
t_Spock* t_Spock_VolverDeMision();

void t_Spock_son_iguales(t_Spock* spock, t_Spock* otro_spock);

#endif /* SPOCK_H_ */
