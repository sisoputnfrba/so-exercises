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
