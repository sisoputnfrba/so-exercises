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

#include "Ejercicio7.h"

int main() {
	pthread_t h1, h2, h3, h4;
	t_queue * jobQueue = queue_create(); //La cola de impresion

	pthread_create(&h1, NULL, (void*) trabajar, jobQueue);
	pthread_create(&h2, NULL, (void*) trabajar, jobQueue);
	pthread_create(&h3, NULL, (void*) trabajar, jobQueue);
	pthread_create(&h4, NULL, (void*) procesar_cola_impresion, jobQueue);

	pthread_join(h1, (void**) NULL);
	pthread_join(h2, (void**) NULL);
	pthread_join(h3, (void**) NULL);
	pthread_join(h4, (void**) NULL);

	return EXIT_SUCCESS;
}

void trabajar(void* args) {
	t_queue * jobQueue = (t_queue *) args;
	for (int i = 0; i < 10; i++) {
		mandar_a_imprimir(jobQueue);
		usleep(1);
	}
}

void procesar_cola_impresion(void* args) {
	t_queue * jobQueue = (t_queue*) args;
	t_print_job* job;
	while ((job = queue_pop(jobQueue)) != NULL) {
		printf("Imprimiendo trabajo de PC %d , datos a imprimir: %s\n", job->pc,
				job->data);
	}
	printf("No hay mas datos para imprimir!.|n");
}

void mandar_a_imprimir(t_queue* jobQueue) {
	t_print_job * job = malloc(sizeof(t_print_job));
	job->data = crear_data();
	job->pc = getpid();
	queue_push(jobQueue, job);
}

/**
 * Genera un string de 9 caracteres alfanumericos random
 */
char * crear_data() {
	static const char alphanum[] =
			"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

	char* data = malloc(10);
	for (int i = 0; i < 9; ++i)
		data[i] = alphanum[rand() % (sizeof(alphanum) - 1)];

	data[9] = '\0';

	return data;
}

