/*
 * Mision.c
 *
 *  Created on: Apr 3, 2012
 *      Author: shinichi
 */


#include "Mision.h"

#include <stdlib.h>
#include <string.h>

t_mision* t_mision_crear(char* mensaje) {
	t_mision* mision = malloc(sizeof(t_mision));
	mision->informacionCodificada = strdup(mensaje);
	mision->longitudInformacionCodificada = strlen(mision->informacionCodificada);
	return mision;
}

void t_mision_destroy(t_mision* mision) {
	free(mision->informacionCodificada);
	free(mision);
}
