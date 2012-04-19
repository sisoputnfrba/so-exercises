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

#include "Ejercicio9.h"

#define MAX_BUFFER_SIZE  200
#define PORT 3200
sem_t sem_conexion;
pthread_mutex_t mutex_queue;
t_queue* message_queue;
int client_socket;

int main() {

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
	int yes = 0;
	setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
	struct sockaddr_in* localAddress = malloc(sizeof(struct sockaddr_in));
	struct sockaddr_in* serverAddress = malloc(sizeof(struct sockaddr_in));
	localAddress->sin_addr.s_addr = INADDR_ANY;
	localAddress->sin_port = htons(PORT + 1);
	localAddress->sin_family = AF_INET;
	if (bind(server_sock, (struct sockaddr*) localAddress, (socklen_t) sizeof(struct sockaddr_in)) == -1) {
		perror("bind");
	}

	serverAddress->sin_addr.s_addr = inet_addr("127.0.0.1");
	serverAddress->sin_port = htons(PORT);
	serverAddress->sin_family = AF_INET;
	if (connect(server_sock, (struct sockaddr*) serverAddress, sizeof(struct sockaddr_in)) == -1) {
		perror("connect");
	}

	client_socket = server_sock;
	sem_post(&sem_conexion);

	while (true) {
		memset(buffer, '\0', MAX_BUFFER_SIZE);
		int recvd = recv(client_socket, buffer, sizeof(int), MSG_WAITALL);
		if (recvd <= 0) {
			if (recvd == -1) {
				perror("recv");
			}

			close(client_socket);
			break;
		}

		int lenCadena;
		memcpy(&lenCadena, buffer, sizeof(int));
		recvd = recv(client_socket, buffer, lenCadena, MSG_WAITALL);
		if (recvd <= 0) {
			if (recvd == -1) {
				perror("recv");
			}

			close(client_socket);
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
	while (fgets(cadena, MAX_BUFFER_SIZE, stdin) != NULL) {
		char* mensaje = malloc(sizeof(int) + strlen(cadena) + 1);
		int len = strlen(cadena) + 1;
		int tmpSize = 0;
		memcpy(mensaje, &len, tmpSize = sizeof(int));
		memcpy(mensaje + tmpSize, cadena, strlen(cadena) + 1);

		if (send(client_socket, mensaje, len + tmpSize, MSG_NOSIGNAL) <= 0) {
			close(client_socket);
		}
	}

	if (cadena != NULL)
		free(cadena);
}

void queue_sync_push(t_queue * queue, void *element) {
	pthread_mutex_lock(&mutex_queue);
	queue_push(queue, element);
	pthread_mutex_unlock(&mutex_queue);

}

void *queue_sync_pop(t_queue * queue) {
	pthread_mutex_lock(&mutex_queue);
	void* element = queue_pop(queue);
	pthread_mutex_unlock(&mutex_queue);
	return element;
}

