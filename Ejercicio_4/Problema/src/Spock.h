/*
 * Spock.h
 *
 *  Created on: Apr 3, 2012
 *      Author: shinichi
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
