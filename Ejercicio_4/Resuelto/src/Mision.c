/*
 * Mision.c
 *
 *  Created on: Apr 3, 2012
 *      Author: shinichi
 */


#include "Mision.h"

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

t_stream* t_mision_serialize(t_mision* mision) {
	int offset = 0;
	t_stream *stream = t_stream_create(strlen(mision->informacionCodificada) + 1 + sizeof(mision->longitudInformacionCodificada));

	memcpy(stream->data + offset, mision->informacionCodificada, strlen(mision->informacionCodificada) + 1);
	offset += strlen(mision->informacionCodificada) + 1;

	memcpy(stream->data + offset, &mision->longitudInformacionCodificada, sizeof(mision->longitudInformacionCodificada));
	offset += sizeof(mision->longitudInformacionCodificada);

	return stream;
}

t_mision* t_mision_deserialize(char* stream, int* size) {
	t_mision* mision = malloc(sizeof(t_mision));
	int offset = 0;

	char* info = strdup(stream + offset);
	mision->informacionCodificada = info;
	offset += strlen(info) + 1;

	memcpy(&mision->longitudInformacionCodificada, stream + offset, sizeof(mision->longitudInformacionCodificada));
	offset += sizeof(mision->longitudInformacionCodificada);

	*size = offset;

	return mision;
}
