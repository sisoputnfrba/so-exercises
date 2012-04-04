/*
 * Ejercicio4.c
 *
 *  Created on: 11/03/2012
 *      Author: sebastian
 */

#include "Ejercicio4.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <memory.h>
#include <assert.h>

/*
 * Por una cuestion de simplicidad del ejercicio
 * el stream resultante de la serializacion es grabado a un archivo
 * Si se reemplazaran los write, por send y los read por recv
 * se puede usar para armar un protocolo de comunicacion simple
 * en el que podemos enviar estructuras complejas.
 */


int main(void) {
	t_Spock* spock_a_enviar = t_Spock_CrearSpock();
	t_Spock_EnviarAMision(spock_a_enviar);

	t_Spock* spock_recibido = t_Spock_VolverDeMision();

	t_Spock_Destruir(spock_a_enviar);
	t_Spock_Destruir(spock_recibido);
	return EXIT_SUCCESS;
}
