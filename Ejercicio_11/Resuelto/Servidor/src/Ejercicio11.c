/*
 * Ejercicio5.c
 *
 *  Created on: 11/03/2012
 *      Author: sebastian
 */
#include "Ejercicio11.h"
#define MAX_BUFFER_SIZE  200

int port;

/*
 * Para evitar el uso de un socket global, se podria implementar una cola de mensajes
 * entre el hilo que recibe de consola y el hilo de comunicaciones asi este es el unico que se relaciona con el socket
 * Para esto es necesario aplicarle locks al TAD de queue actual.
 */
int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("Cantidad invalida de argumentos"
				" debe ingresar el puerto como parametro!\n");
		return EXIT_FAILURE;
	}
	port = atoi(argv[1]);
	iniciar_conexion();
	return EXIT_SUCCESS;
}

void iniciar_conexion() {
	fd_set set_master, set_copia;

	char buffer[MAX_BUFFER_SIZE];
	int server_socket = socket(AF_INET, SOCK_STREAM, 0);
	unsigned int len = sizeof(struct sockaddr);
	int yes = 0;

	if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
		perror("setsockopt");
	}

	struct sockaddr_in* local_address = malloc(sizeof(struct sockaddr_in));
	struct sockaddr_in* server_address = malloc(sizeof(struct sockaddr_in));
	local_address->sin_addr.s_addr = inet_addr("127.0.0.1");
	local_address->sin_port = htons(port);
	local_address->sin_family = AF_INET;
	if (bind(server_socket, (struct sockaddr*) local_address,
			(socklen_t) sizeof(struct sockaddr_in)) == -1) {
		perror("bind");
	}

	if (listen(server_socket, 10) == -1) {
		perror("listen");
	}

	FD_ZERO(&set_master);
	FD_SET(server_socket, &set_master);

	int descriptor_mas_alto = server_socket;
	printf("Servidor listo para escuchar conexiones\n");
	while (true) {
		set_copia = set_master;
		int i = select(descriptor_mas_alto + 1, &set_copia, NULL, NULL, NULL);
		if (i == -1) {
			perror("select");
			break;
		}

		int n_descriptor = 0;
		while (n_descriptor <= descriptor_mas_alto) {
			if (FD_ISSET(n_descriptor,&set_copia)) {
				if (n_descriptor == server_socket) {
					int client_socket;
					if ((client_socket = accept(server_socket, (struct sockaddr*) server_address, &len)) == -1) {
						printf("El socket %d ha producido un error"
								"y ha sido desconectado.\n",
								client_socket);
						perror("accept");
						n_descriptor++;
						continue;
					}
					printf("El socket %d se ha conectado al servidor.\n",
							client_socket);
					FD_SET(client_socket, &set_master);
					if (client_socket > descriptor_mas_alto) {
						descriptor_mas_alto = client_socket;
					}
				} else {
					memset(buffer, '\0', MAX_BUFFER_SIZE);
					int recvd = recv(n_descriptor, buffer, sizeof(int), MSG_WAITALL);
					if (recvd <= 0) {
						if (recvd == -1) {
							perror("recv");
						}
						printf("El socket %d ha producido un error "
								"y ha sido desconectado.\n",
								n_descriptor);
						close(n_descriptor);
						FD_CLR(n_descriptor, &set_master);
						n_descriptor++;
						continue;
					}

					int longitud_cadena;
					memcpy(&longitud_cadena, buffer, sizeof(int));
					recvd = recv(n_descriptor, buffer, longitud_cadena, MSG_WAITALL);
					if (recvd <= 0) {
						if (recvd == -1) {
							perror("recv");
						}
						printf("El socket %d ha producido un error "
								"y ha sido desconectado.\n",
								n_descriptor);
						close(n_descriptor);
						FD_CLR(n_descriptor, &set_master);
						n_descriptor++;
						continue;
					}

					printf(
							"Ha recibido del cliente el siguiente mensaje: %s  \n",
							buffer);

					for (int j = server_socket; j <= descriptor_mas_alto; j++) {
						if (j != server_socket && j != n_descriptor) {
							char* mensaje = malloc(sizeof(int) + longitud_cadena);
							int longitud = longitud_cadena;
							int tmp_size = 0;
							memcpy(mensaje, &longitud, tmp_size = sizeof(int));
							memcpy(mensaje + tmp_size, buffer, longitud_cadena);
							printf("Enviando mensaje %s al socket %d", mensaje, j);
							if (send(j, mensaje, longitud + tmp_size, MSG_NOSIGNAL) <= 0) {
								printf("El socket %d ha producido "
										"un error y ha sido desconectado.\n", j);
								close(j);
								FD_CLR(j, &set_master);
							}

							free(mensaje);
						}
					}
				}
			}

			n_descriptor++;
		}

	}

	free(server_address);
	free(local_address);

}

