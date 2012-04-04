/*
 * Mision.h
 *
 *  Created on: Apr 3, 2012
 *      Author: shinichi
 */

#ifndef MISION_H_
#define MISION_H_

typedef struct {
	char* informacionCodificada;
	int longitudInformacionCodificada;
}__attribute__((packed)) t_mision;

t_mision* t_mision_crear(char* mensaje);
void t_mision_destroy(t_mision* mision);

#endif /* MISION_H_ */
