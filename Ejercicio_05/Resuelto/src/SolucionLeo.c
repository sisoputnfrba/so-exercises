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

#include "SolucionLeo.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#include <sys/types.h>

#define SALDO 100
int saldo_inicial;
pthread_mutex_t mutex_compras; //Semaforo MUTEX

int main(void) {
	pthread_t h1, h2;
	saldo_inicial = SALDO;
	pthread_mutex_init(&mutex_compras, NULL); //Los Mutex deben inicializarse siempre y solo una vez llamando a mutex_init
	pthread_create(&h1, NULL, (void*) compras_mensuales, "Julieta");
	pthread_create(&h2, NULL, (void*) compras_mensuales, "Leo");
	pthread_join(h1, (void **) NULL);
	pthread_join(h2, (void **) NULL);

	return EXIT_SUCCESS;
}

void compras_mensuales(void* args) {
	char* nombre = (char*) args;

	for (int i = 0; i < (SALDO / 10); i++) {
		hacer_compras(10, nombre);
		if (consulta_saldo() < 0) {
			printf("La cuenta esta en rojo!! El almacenero nos va a matar!\n");
		}
	}
}

int consulta_saldo() {
	return saldo_inicial;
}

void hacer_compras(int monto, const char* nombre) {
	//Trata de adquirir el lock del mutex, si nadie mas lo adquirio lograra entrar a la region critica
	//Si otro ya entro antes, debera esperar a que libere el lock para poder entrar
	pthread_mutex_lock(&mutex_compras);

	if (consulta_saldo() >= monto) {
		printf("Hay saldo suficiente %s esta por comprar.\n", nombre);
		usleep(1);
		comprar(monto);
		printf("%s acaba de comprar.\n", nombre);
	} else
		printf("No queda suficiente saldo (%d)  para que %s haga las compras.\n",
				consulta_saldo(), nombre);

	pthread_mutex_unlock(&mutex_compras); //Liberamos el Mutex para que el otro pueda operar.
	usleep(1);
}

void comprar(int monto) {
	saldo_inicial = saldo_inicial - monto;
}
