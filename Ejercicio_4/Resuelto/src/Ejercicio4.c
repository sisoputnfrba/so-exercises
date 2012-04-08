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

#include "Ejercicio4.h"

#include <stdlib.h>
#include <stdio.h>

/*
 * Por una cuestion de simplicidad del ejercicio
 * el stream resultante de la serializacion es grabado a un archivo
 * Si se reemplazaran los write, por send y los read por recv
 * se puede usar para armar un protocolo de comunicacion simple
 * en el que podemos enviar estructuras complejas.
 */
int main(void) {
	t_spock* spock_a_enviar = spock_crear();
	spock_enviar_a_mision(spock_a_enviar);

	t_spock* spock_recibido = spock_volver_de_mision();
	spock_es_igual(spock_a_enviar, spock_recibido);

	spock_print(spock_a_enviar);
	printf("---------------------------------\n");
	spock_print(spock_recibido);

	spock_destroy(spock_a_enviar);
	spock_destroy(spock_recibido);
	return EXIT_SUCCESS;
}
