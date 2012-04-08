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

#include "Wendys.h"

t_hamburguesa hamburguesa;

int main(void) {
	pthread_t h1, h2, h3, h4, h5, h6, h7, h8;
	hamburguesa.embalada = false;
	hamburguesa.ingredientes = queue_create();

	pthread_create(&h1, NULL, (void*) agregar_pan_inferior, NULL);
	pthread_create(&h2, NULL, (void*) agregar_condimento, NULL);
	pthread_create(&h3, NULL, (void*) agregar_carne, NULL);
	pthread_create(&h4, NULL, (void*) agregar_queso, NULL);
	pthread_create(&h5, NULL, (void*) agregar_panceta, NULL);
	pthread_create(&h6, NULL, (void*) agregar_lechuga, NULL);
	pthread_create(&h7, NULL, (void*) agregar_tomate, NULL);
	pthread_create(&h7, NULL, (void*) agregar_pan_superior, NULL);
	pthread_create(&h8, NULL, (void*) entregar, NULL);

	pthread_join(h1, (void**) NULL);
	pthread_join(h2, (void**) NULL);
	pthread_join(h3, (void**) NULL);
	pthread_join(h4, (void**) NULL);
	pthread_join(h5, (void**) NULL);
	pthread_join(h6, (void**) NULL);
	pthread_join(h7, (void**) NULL);
	pthread_join(h8, (void**) NULL);

	return EXIT_SUCCESS;
}

void agregar_pan_inferior() {
	agregar(PANINFERIOR);
}

void agregar_condimento() {
	agregar(CONDIMENTOS);
}

void agregar_carne() {
	agregar(CARNE);
}

void agregar_queso() {
	agregar(QUESO);
}

void agregar_panceta() {
	agregar(PANCETA);
}

void agregar_lechuga() {
	agregar(LECHUGA);
}

void agregar_tomate() {
	agregar(TOMATE);
}

void agregar_pan_superior() {
	agregar(PANSUPERIOR);
}

void entregar() {
	if (!esta_bien_armada()){
		printf("Error en el armado de la hamburguesa!! El cliente se fue a comerse un triple bacon a mc :( \n");
	}
	else {
		printf("Hamburguesa armada perfectamente!! Le hemos tapado 5 arterias al cliente!! :)\n");
	}
}

void agregar(t_Ingredientes ingrediente) {
	printf("Agregando ingrediente %s\n", ingrediente_to_string(ingrediente));
	int * i = malloc(sizeof(int));
	*i = ingrediente;
	queue_push(hamburguesa.ingredientes, i);
}

bool esta_bien_armada() {
	/*Esta correctamente armada si tiene todos los ingredientes,
		 *  y los tiene definidos en el orden dado por el enum t_Ingredientes*/

	for (int i = 0; (((t_Ingredientes) i) <= PANSUPERIOR); i++) {
		t_Ingredientes ingrediente_correcto = (t_Ingredientes) i;
		t_Ingredientes ingrediente_hamburguesa;

		int* ingrediente = queue_pop(hamburguesa.ingredientes);

		if (ingrediente == NULL) {
			printf("Faltaron ingredientes!\n");
			return false;
		}

		ingrediente_hamburguesa = (t_Ingredientes) *ingrediente;
		if (ingrediente_hamburguesa != ingrediente_correcto) {
			printf("Ingrediente incorrecto debia ser %s y era %s\n",
					ingrediente_to_string(ingrediente_correcto),
					ingrediente_to_string(ingrediente_hamburguesa));

			free(ingrediente);
			return false;
		}
	}

	return true;
}

char* ingrediente_to_string(t_Ingredientes ingrediente) {
	char* ingredienteChar;
	switch (ingrediente) {
	case PANINFERIOR:
		ingredienteChar = "PANINFERIOR";
		break;
	case PANSUPERIOR:
		ingredienteChar = "PANSUPERIOR";
		break;
	case CARNE:
		ingredienteChar = "CARNE";
		break;
	case QUESO:
		ingredienteChar = "QUESO";
		break;
	case PANCETA:
		ingredienteChar = "PANCETA";
		break;
	case LECHUGA:
		ingredienteChar = "LECHUGA";
		break;
	case TOMATE:
		ingredienteChar = "TOMATE";
		break;
	case CONDIMENTOS:
		ingredienteChar = "CONDIMENTOS";
		break;
	default:
		ingredienteChar = "Desconocido!";
		break;
	}

	return ingredienteChar;

}
