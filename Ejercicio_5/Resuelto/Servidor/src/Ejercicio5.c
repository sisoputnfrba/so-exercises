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

#include "Ejercicio5.h"

#define MAX_BUFFER_SIZE  200
#define PORT 3200
sem_t sem_conexion;
pthread_mutex_t mutex_queue;
t_queue* message_queue;
int client_sock;

/*
 * Para evitar el uso de un socket global, se podria implementar una cola de mensajes
 * entre el hilo que recibe de consola y el hilo de comunicaciones asi este es el unico que se relaciona con el socket
 * Para esto es necesario aplicarle locks al TAD de queue actual.
 */
int main(void) {
	pthread_t h1;
	sem_init(&sem_conexion, 0, 0);
	pthread_mutex_init(&mutex_queue, NULL);
	pthread_create(&h1, NULL, (void*) iniciar_conexion, NULL);
	comunicarse();
	pthread_join(h1, (void**) NULL);
	return EXIT_SUCCESS;
}

void iniciar_conexion() {

	char buffer[MAX_BUFFER_SIZE];
	int server_sock = socket(AF_INET, SOCK_STREAM, 0);
	unsigned int len = sizeof(struct sockaddr);
	int yes = 0;
	if (setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
		perror("setsockopt");
	}
	struct sockaddr_in* localAddress = malloc(sizeof(struct sockaddr_in));
	struct sockaddr_in* serverAddress = malloc(sizeof(struct sockaddr_in));
	localAddress->sin_addr.s_addr = inet_addr("127.0.0.1");
	localAddress->sin_port = htons(PORT);
	localAddress->sin_family = AF_INET;
	if (bind(server_sock, (struct sockaddr*) localAddress, (socklen_t) sizeof(struct sockaddr_in)) == -1) {
		perror("bind");
	}

	if (listen(server_sock, 10) == -1) {
		perror("listen");
	}

	if ((client_sock = accept(server_sock, (struct sockaddr*) serverAddress, &len)) == -1) {
		perror("accept");
	}

	sem_post(&sem_conexion);

	while (true) {
		/*
		 * Para no tener perdida de datos se usa el flag MSG_WAITALL que lo que hace es esperar a que el recv llene el buffer
		 * Con size bytes. Al poner este flag no se puede hacer que espere MAX_SIZE_BUFFER pq sino hasta que manden
		 * esa cantidad el recv quedara colgado.
		 *
		 * Es por eso que se hace UN UNICO ENVIO con un int y una cadena, consumiendo primero el int que representa
		 * la cantidad de bytes que se deben recibir en la cadena.
		 *
		 * Es importante recalcar que esto no es fraccionar un paquete, ya que se hace un unico envio y este se consume en 2 llamadas.
		 * Si hicieramos 2 send (uno con el int y otro con la cadena) estaria mal desde el punto de vista de redes ya que habria
		 * fraccionamiento de paquetes (cuando un paquete es una unidad indivisible que se transmite por la red)
		 */
		memset(buffer, '\0', MAX_BUFFER_SIZE);
		int recvd = recv(client_sock, buffer, sizeof(int), MSG_WAITALL);
		if (recvd <= 0) {
			if (recvd == -1) {
				perror("recv");
			}

			close(client_sock);
			break;
		}

		int lenCadena;
		memcpy(&lenCadena, buffer, sizeof(int));
		recvd = recv(client_sock, buffer, lenCadena, MSG_WAITALL);
		if (recvd <= 0) {
			if (recvd == -1) {
				perror("recv");
			}

			close(client_sock);
			break;
		}

		printf("Ha recibido del cliente el siguiente mensaje: %s  \n", buffer);
	}

	free(serverAddress);
	free(localAddress);
}

void comunicarse() {
	sem_wait(&sem_conexion);
	char* cadena = malloc(MAX_BUFFER_SIZE);
	while (fgets(cadena, MAX_BUFFER_SIZE, stdin) != NULL) {
		char* mensaje = malloc(sizeof(int) + strlen(cadena) + 1); //serializamos "on-the fly" un int junto con la cadena para que esta pueda ser de tamaño variable
		int len = strlen(cadena) + 1;
		int tmpSize = 0;
		memcpy(mensaje, &len, tmpSize = sizeof(int));
		memcpy(mensaje + tmpSize, cadena, strlen(cadena) + 1);

		if (send(client_sock, mensaje, len + tmpSize, MSG_NOSIGNAL) <= 0)
			close(client_sock);
	}

	if (cadena != NULL)
		free(cadena);
}

