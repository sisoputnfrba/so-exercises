/*
 * Ejercicio4.c
 *
 *  Created on: 11/03/2012
 *      Author: sebastian
 */

#include "Ejercicio4.h"
#include <assert.h>
#include <string.h>

/*
 * Por una cuestion de simplicidad del ejercicio
 * el stream resultante de la serializacion es grabado a un archivo
 * Si se reemplazaran los write, por send y los read por recv
 * se puede usar para armar un protocolo de comunicacion simple
 * en el que podemos enviar estructuras complejas.
 */


const char* letras = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
static char* mensajeRandom();

int main(void) {
	t_Spock* spock = t_Spock_CrearSpock();
	t_Spock_EnviarAMision(spock);
	return EXIT_SUCCESS;
}

t_Spock* t_Spock_CrearSpock() {
	t_Spock* spock = malloc(sizeof(t_Spock));
	spock->edad = 40;
	spock->nombre = strdup("Roberto Spock");

	spock->mascota = t_mascota_crear("Babu", true, 5);
	spock->listaDeVillanos = list_create();

	list_add(spock->listaDeVillanos, t_villano_crear("Borg Queen", 34));
	list_add(spock->listaDeVillanos, t_villano_crear("Locotus", 20));
	list_add(spock->listaDeVillanos, t_villano_crear("Dukat", 67));

	char* mensaje = mensajeRandom();
	spock->mision = t_mision_crear(mensaje);

	return spock;
}

void t_Spock_Destruir(t_Spock* spock) {
	free(spock->nombre);
	t_mascota_destroy(spock->mascota);
	t_mision_destroy(spock->mision);
	list_destroy_and_destroy_elements(spock->listaDeVillanos, t_Villano_Destroyer);
	free(spock);
}

void t_Villano_Destroyer(void* villano) {
	free(villano);
}

void t_Spock_EnviarAMision(t_Spock* spock) {

	t_stream* stream_spock_write = t_Spock_Serialize(spock);
	FILE* file = fopen("./spock.bin", "w");
	fwrite(stream_spock_write->data, stream_spock_write->size, 1, file);
	fflush(file);
	fclose(file);

	struct stat statSpock;
	stat("./spock.bin", &statSpock);
	file = fopen("./spock.bin", "r");
	t_stream* stream_spock_read = t_stream_create(statSpock.st_size);
	fread(stream_spock_read->data, statSpock.st_size, 1, file);
	fclose(file);

	t_Spock* spockRecibido = t_Spock_deserialize(stream_spock_read->data, &stream_spock_read->size);

	//Comparar las estructuras campo por campo
	t_Spock_CompararSpocks(spock, spockRecibido);

}

void t_Spock_CompararSpocks(t_Spock* spockEnviado, t_Spock* spockRecibido) {

	assert(strcmp(spockEnviado->nombre, spockRecibido->nombre) == 0);
	printf("Nombre Spock original: %s - Nombre Spock Nuevo %s \n",
			spockEnviado->nombre, spockRecibido->nombre);

	assert(spockEnviado->edad == spockRecibido->edad);
	printf("Edad Spock original: %d - Edad Spock Nuevo %d \n", spockEnviado->edad,
			spockRecibido->edad);

	assert(strcmp(spockEnviado->mascota->apodo, spockRecibido->mascota->apodo) == 0);
	printf("Apodo mascota Spock original: %s - Apodo mascota Spock Nuevo %s \n",
			spockEnviado->mascota->apodo, spockRecibido->mascota->apodo);

	assert(spockEnviado->mascota->daVueltas == spockRecibido->mascota->daVueltas);
	printf("Da Vueltas mascota Spock original: %s - Da Vueltas mascota Spock Nuevo %s \n",
			(spockEnviado->mascota->daVueltas) ? "true" : "false",
			(spockRecibido->mascota->daVueltas) ? "true" : "false");

	assert(spockEnviado->mascota->edad == spockRecibido->mascota->edad);
	printf("Edad mascota Spock original: %d - Edad mascota Spock Nuevo %d \n",
			spockEnviado->mascota->edad, spockRecibido->mascota->edad);

	assert(strcmp(spockEnviado->mision->informacionCodificada, spockRecibido->mision->informacionCodificada) == 0);
	printf("Informacion codificada Spock original: %s - Informacion Codificada Spock Nuevo %s \n",
			spockEnviado->mision->informacionCodificada,
			spockRecibido->mision->informacionCodificada);

	assert(spockEnviado->mision->longitudInformacionCodificada == spockRecibido->mision->longitudInformacionCodificada);
	printf("Longitud Info codificada Spock original: %d - Longitud Info codificada Spock Nuevo %d \n",
			spockEnviado->mision->longitudInformacionCodificada,
			spockRecibido->mision->longitudInformacionCodificada);

	int i;
	for (i = 0; i < list_size(spockEnviado->listaDeVillanos); ++i) {
		t_Villano* villano_enviado = list_get(spockEnviado->listaDeVillanos, i);
		t_Villano* villano_recibido = list_get(spockEnviado->listaDeVillanos, i);

		assert(strcmp(villano_enviado->nombre, villano_recibido->nombre) == 0);
		printf("Villano enviado nombre: %s - Villano recibido nombre: %s\n", villano_enviado->nombre, villano_recibido->nombre);

		assert(villano_enviado->edad == villano_recibido->edad);
		printf("Villano enviado edad: %d - Villano recibido edad: %d\n", villano_enviado->edad, villano_recibido->edad);
	}
}

t_mascota* t_mascota_crear(char* apodo, bool daVueltas, int edad) {
	t_mascota* mascota = malloc(sizeof(t_mascota));
	mascota->apodo = strdup(apodo);
	mascota->daVueltas = daVueltas;
	mascota->edad = edad;

	return mascota;
}

void t_mascota_destroy(t_mascota* mascota) {
	free(mascota->apodo);
	free(mascota);
}

t_Villano* t_villano_crear(char* nombre, int edad) {
	t_Villano* villano = malloc(sizeof(t_Villano));
	strncpy(villano->nombre, nombre, 24);
	villano->edad = edad;
	return villano;
}

void t_villano_destroy(t_Villano* villano) {
	free(villano);
}

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

static char* mensajeRandom() {
	return "ABCDEFGHI";
}

t_stream* t_stream_create(int size) {
	t_stream* stream = malloc(sizeof(t_stream));
	stream->size = size;
	stream->data = malloc(size);
	return stream;
}

void t_stream_destroy(t_stream* stream) {
	free(stream->data);
	free(stream);
}

t_stream* t_Spock_Serialize(t_Spock* spock) {
	int offset = 0;
	t_stream* stream_spock = t_stream_create(sizeof(spock->edad) + strlen(spock->nombre) + 1);

	memcpy(stream_spock->data + offset, &spock->edad, sizeof(spock->edad));
	offset += sizeof(spock->edad);

	memcpy(stream_spock->data + offset, spock->nombre, strlen(spock->nombre) + 1);
	offset += strlen(spock->nombre) + 1;

	t_stream* stream_mascota = t_mascota_serialize(spock->mascota);
	stream_spock->data = realloc(stream_spock->data, stream_spock->size + stream_mascota->size);
	memcpy(stream_spock->data + offset, stream_mascota->data, stream_mascota->size);
	stream_spock->size += stream_mascota->size;
	offset += stream_mascota->size;
	t_stream_destroy(stream_mascota);

	t_stream* stream_mision = t_mision_serialize(spock->mision);
	stream_spock->data = realloc(stream_spock->data, stream_spock->size + stream_mision->size);
	memcpy(stream_spock->data + offset, stream_mision->data, stream_mision->size);
	stream_spock->size += stream_mision->size;
	offset += stream_mision->size;
	t_stream_destroy(stream_mision);

	void serialize_element_villano(void* element) {
		t_Villano* villano = element;

		t_stream* stream_villano = t_villano_serialize(villano);
		stream_spock->data = realloc(stream_spock->data, stream_spock->size + stream_villano->size);
		memcpy(stream_spock->data + offset, stream_villano->data, stream_villano->size);
		stream_spock->size += stream_villano->size;
		offset += stream_villano->size;
		t_stream_destroy(stream_villano);
	}

	int count_villanos = list_size(spock->listaDeVillanos);
	memcpy(stream_spock->data + offset, &count_villanos, sizeof(count_villanos));
	stream_spock->size += sizeof(count_villanos);
	offset += sizeof(count_villanos);

	list_iterate(spock->listaDeVillanos, serialize_element_villano);

	return stream_spock;
}

t_Spock* t_Spock_deserialize(char* stream, int* size) {
	t_Spock* spock = malloc(sizeof(t_Spock));
	int offset = 0, tmp_size = 0, i = 0;

	memcpy(&spock->edad, stream + offset, tmp_size = sizeof(spock->edad));
	offset += tmp_size;

	spock->nombre = strdup(stream + offset);
	offset += strlen(spock->nombre) + 1;

	spock->mascota = t_mascota_deserialize(stream + offset, &tmp_size);
	offset += tmp_size;

	spock->mision = t_mision_deserialize(stream + offset, &tmp_size);
	offset += tmp_size;

	int elements_villano = 0;
	memcpy(&elements_villano, stream + offset, sizeof(elements_villano));
	offset += sizeof(elements_villano);

	t_list* villanos = list_create();
	for (i = 0; i < elements_villano; ++i) {
		t_Villano* villano = t_villano_deserialize(stream + offset, &tmp_size);
		offset += tmp_size;
		list_add(villanos, villano);
	}
	spock->listaDeVillanos = villanos;

	*size = offset;

	return spock;
}


t_stream* t_mascota_serialize(t_mascota* mascota) {
	int offset = 0;
	t_stream *stream = t_stream_create(sizeof (mascota->edad)
										+ sizeof (mascota->daVueltas)
										+ strlen(mascota->apodo) + 1);

	memcpy(stream->data + offset, &mascota->edad, sizeof(mascota->edad));
	offset += sizeof(mascota->edad);

	memcpy(stream->data + offset, &mascota->daVueltas, sizeof(mascota->daVueltas));
	offset += sizeof(mascota->daVueltas);

	memcpy(stream->data + offset, mascota->apodo, strlen(mascota->apodo) + 1);
	offset += strlen(mascota->apodo) + 1;

	return stream;
}

t_mascota* t_mascota_deserialize(char* stream, int* size) {
	t_mascota* mascota = malloc(sizeof(t_mascota));
	int offset = 0;

	memcpy(&mascota->edad, stream + offset, sizeof(mascota->edad));
	offset += sizeof(mascota->edad);

	memcpy(&mascota->daVueltas, stream + offset, sizeof(mascota->daVueltas));
	offset += sizeof(mascota->daVueltas);

	char* apodo = strdup(stream + offset);
	mascota->apodo = apodo;
	offset += strlen(apodo) + 1;

	*size = offset;

	return mascota;
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

t_stream* t_villano_serialize(t_Villano* villano) {
	t_stream *stream = t_stream_create(sizeof(t_Villano));
	memcpy(stream->data, villano, sizeof(t_Villano));
	return stream;
}

t_Villano* t_villano_deserialize(char* stream, int* size) {
	t_Villano *villano = malloc(sizeof(t_Villano));
	memcpy(villano, stream, sizeof(t_Villano));

	*size = sizeof(t_Villano);

	return villano;
}
