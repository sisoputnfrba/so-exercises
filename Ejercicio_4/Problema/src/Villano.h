/*
 * Villano.h
 *
 *  Created on: Apr 3, 2012
 *      Author: shinichi
 */

#ifndef VILLANO_H_
#define VILLANO_H_

typedef struct {
	char nombre[25];
	int edad;
}__attribute__((packed)) t_Villano;

t_Villano* t_villano_crear(char* nombre, int edad);
void t_villano_destroy(t_Villano* villano);

#endif /* VILLANO_H_ */
