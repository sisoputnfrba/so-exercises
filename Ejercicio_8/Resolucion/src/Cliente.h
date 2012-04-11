/*
 * Cliente.h
 *
 *  Created on: Apr 10, 2012
 *      Author: shinichi
 */

#ifndef CLIENTE_H_
#define CLIENTE_H_

#include <stdio.h>

typedef struct {
	int codigo_cliente;
	char* nombre;
	char* apellido;
} t_cliente;

t_cliente* cliente_create(char* nombre, char* apellido, int codigo_cliente);
void cliente_destroy(t_cliente* cliente);

t_cliente* cliente_from_file(FILE* file);

#endif /* CLIENTE_H_ */
