/*
 * Ejercicio4.c
 *
 *  Created on: 11/03/2012
 *      Author: sebastian
 */

#include "Ejercicio4.h"
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
	struct stat statSpock;
	FILE* file = fopen("./spock.bin", "w");
	fwrite(spock, sizeof(t_Spock), 1, file);
	fflush(file);
	t_Spock* spockRecibido = malloc(sizeof(t_Spock));
	stat("./spock.bin", &statSpock);

	fread(spockRecibido, statSpock.st_size, 1, file);

	//1° Metodo de comparacion: Comparar los streams
	if (memcmp(spock, spockRecibido, statSpock.st_size) != 0) {
		printf("Los spock son distintos!!\n");
	}
	//2° Metodo, comparar las estructuras campo por campo
	t_Spock_CompararSpocks(spock, spockRecibido);

}

void t_Spock_CompararSpocks(t_Spock* spockEnviado, t_Spock* spockRecibido) {

	printf("Edad Spock original: %d Edad Spock Nuevo %d \n", spockEnviado->edad,
			spockRecibido->edad);
	printf("Nombre Spock original: %s Nombre Spock Nuevo %s \n",
			spockEnviado->nombre, spockRecibido->nombre);
	printf("Apodo mascota Spock original: %s Apodo mascota Spock Nuevo %s \n",
			spockEnviado->mascota->apodo, spockRecibido->mascota->apodo);
	printf(
			"Da Vueltas mascota Spock original: %s Da Vueltas mascota Spock Nuevo %s \n",
			(spockEnviado->mascota->daVueltas) ? "true" : "false",
			(spockRecibido->mascota->daVueltas) ? "true" : "false");
	printf("Edad mascota Spock original: %d Edad mascota Spock Nuevo %d \n",
			spockEnviado->mascota->edad, spockRecibido->mascota->edad);
	printf(
			"Informacion codificada Spock original: %s Informacion Codificada Spock Nuevo %s \n",
			spockEnviado->mision->informacionCodificada,
			spockRecibido->mision->informacionCodificada);
	printf(
			"Longitud Informacion codificada Spock original: %d Edad Spock Nuevo %d \n",
			spockEnviado->mision->longitudInformacionCodificada,
			spockEnviado->mision->longitudInformacionCodificada);

	list_iterate(spockEnviado->listaDeVillanos, ChequearVillanos);
	list_iterate(spockRecibido->listaDeVillanos, ChequearVillanos);
}

void ChequearVillanos(void* villano) {
	t_Villano* v = villano;
	printf("Edad villano %d\n", v->edad);
	printf("Nombre villano %s\n", v->nombre);
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
	unsigned long int longitud = rand() % strlen(letras);
    char *stringRandom = malloc(longitud);

    int i;
    for (i = 0; i < longitud; ++i) {
        stringRandom[i] = letras[rand() % (sizeof(letras) - 1)];
    }

	return stringRandom;
}
