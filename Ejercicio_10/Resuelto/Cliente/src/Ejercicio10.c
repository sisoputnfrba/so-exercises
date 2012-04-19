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

#include "Ejercicio10.h"
#define MAX_BUFFER_SIZE  200

int puerto_cliente;
int puerto_servidor;
sem_t sem_conexion;
int socket_cliente;

int main(int argc, char* argv[]) {
	if (argc != 3) {
		printf(
				"Cantidad invalida de argumentos, debe ingresar primero el puerto servidor y luego el puerto cliente como parametro!\n");
		return EXIT_FAILURE;
	}

	puerto_servidor = atoi(argv[1]);
	puerto_cliente = atoi(argv[2]);

	pthread_t h1;
	sem_init(&sem_conexion, 0, 0);
	pthread_create(&h1, NULL, iniciar_conexion, NULL);
	comunicarse();
	pthread_join(h1, (void**) NULL);
	return EXIT_SUCCESS;
}

void iniciar_conexion() {

	char buffer[MAX_BUFFER_SIZE];
	int server_sock = socket(AF_INET, SOCK_STREAM, 0);
	int yes = 0;

	if (setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
		perror("setsockopt");
	}

	struct sockaddr_in* localAddress = malloc(sizeof(struct sockaddr_in));
	struct sockaddr_in* serverAddress = malloc(sizeof(struct sockaddr_in));
	localAddress->sin_addr.s_addr = INADDR_ANY;
	localAddress->sin_port = htons(puerto_cliente);
	localAddress->sin_family = AF_INET;
	if (bind(server_sock, (struct sockaddr*) localAddress,
			(socklen_t) sizeof(struct sockaddr_in)) == -1)
		perror("bind");

	serverAddress->sin_addr.s_addr = inet_addr("127.0.0.1");
	serverAddress->sin_port = htons(puerto_servidor);
	serverAddress->sin_family = AF_INET;
	if (connect(server_sock, (struct sockaddr*) serverAddress, sizeof(struct sockaddr_in)) == -1) {
		perror("connect");
	}
	socket_cliente = server_sock;
	sem_post(&sem_conexion);
	printf("Cliente esperando respuestas\n");
	while (true) {

		memset(buffer, '\0', MAX_BUFFER_SIZE);
		int recvd = recv(socket_cliente, buffer, sizeof(int), MSG_WAITALL);
		if (recvd <= 0) {
			if (recvd == -1) {
				perror("recv");
			}
			printf("Ha ocurrido un error con el socket %d y ha sido desconectado \n",
					socket_cliente);
			close(socket_cliente);
			break;
		}

		int longitud_cadena;
		memcpy(&longitud_cadena, buffer, sizeof(int));
		recvd = recv(socket_cliente, buffer, longitud_cadena, MSG_WAITALL);
		if (recvd <= 0) {
			if (recvd == -1) {
				perror("recv");
			}
			printf("Ha ocurrido un error con el socket %d y ha sido desconectado \n",
					socket_cliente);
			close(socket_cliente);
			break;
		}

		printf("Ha recibido del servidor el siguiente mensaje: %s \n", buffer);
	}
	free(serverAddress);
	free(localAddress);
}

void comunicarse() {
	sem_wait(&sem_conexion);
	char* cadena = malloc(MAX_BUFFER_SIZE);
	printf("Cliente listo para recibir mensajes por consola\n");
	while (fgets(cadena, MAX_BUFFER_SIZE, stdin) != NULL) {
		char* mensaje = malloc(sizeof(int) + strlen(cadena) + 1);
		int longitud = strlen(cadena) + 1;
		int tmp_size = 0;
		memcpy(mensaje, &longitud, tmp_size = sizeof(int));
		memcpy(mensaje + tmp_size, cadena, strlen(cadena) + 1);

		if (send(socket_cliente, mensaje, longitud + tmp_size, MSG_NOSIGNAL) <= 0) {
			close(socket_cliente);
		}
	}

	if (cadena != NULL) {
		free(cadena);
	}
}

