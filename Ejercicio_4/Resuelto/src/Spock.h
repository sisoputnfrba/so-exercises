/*
 * Spock.h
 *
 *  Created on: Apr 3, 2012
 *      Author: shinichi
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
	int edad;
	t_list* listaDeVillanos;
	t_mascota* mascota;
	t_mision* mision;
}__attribute__((packed)) t_Spock;

t_Spock* t_Spock_CrearSpock();
void t_Spock_Destruir(t_Spock* spock);

t_stream* t_Spock_Serialize(t_Spock* spock);
t_Spock* t_Spock_deserialize(char* stream, int* size);


void t_Spock_EnviarAMision(t_Spock* spock);
t_Spock* t_Spock_VolverDeMision();


#endif /* SPOCK_H_ */
