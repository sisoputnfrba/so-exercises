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
 
#include "Ejercicio6.h"
#define MAX_BUFFER_SIZE  200

int portCliente;
int portServidor;
sem_t semConexion;
int client_sock;
int main (int argc, char* argv[])
{
	if(argc!= 3)
	{
		printf("Cantidad invalida de argumentos, debe ingresar primero el puerto servidor y luego el puerto cliente como parametro!\n");
		return EXIT_FAILURE;
	}
	portServidor=atoi(argv[1]);
	portCliente=atoi(argv[2]);
	pthread_t h1;
	sem_init(&semConexion,0,0);
	pthread_create(&h1,NULL,IniciarConexion,NULL);
	Comunicarse();
	pthread_join(h1,(void**)NULL);
	return EXIT_SUCCESS;
}

void* IniciarConexion(void* args)
{

	char buffer[MAX_BUFFER_SIZE];
	int server_sock=socket(AF_INET,SOCK_STREAM,0);
	int yes=0;
	if(setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &yes,  sizeof(int))==-1)
		perror("setsockopt");
	struct sockaddr_in* localAddress= malloc(sizeof(struct sockaddr_in));
	struct sockaddr_in* serverAddress= malloc(sizeof(struct sockaddr_in));
	localAddress->sin_addr.s_addr=INADDR_ANY;
	localAddress->sin_port=htons(portCliente);
	localAddress->sin_family=AF_INET;
	if(	bind(server_sock,(struct sockaddr*) localAddress,(socklen_t)sizeof(struct sockaddr_in))==-1)
		perror("bind");

	serverAddress->sin_addr.s_addr=inet_addr("127.0.0.1");
	serverAddress->sin_port=htons(portServidor);
	serverAddress->sin_family=AF_INET;
	if(connect(server_sock,(struct sockaddr*)serverAddress,sizeof(struct sockaddr_in))==-1)
		perror("connect");
	client_sock=server_sock;
	sem_post(&semConexion);
	printf("Cliente esperando respuestas\n");
	while(true)
	{

		memset(buffer,'\0',MAX_BUFFER_SIZE);
		int recvd=recv(client_sock,buffer,sizeof(int),MSG_WAITALL);
		if(recvd<=0)
		{
			if(recvd==-1)
			{
				perror("recv");
			}
			printf("Ha ocurrido un error con el socket %d y ha sido desconectado \n",client_sock);
			close(client_sock);
			break;
		}

		int lenCadena;
		memcpy(&lenCadena,buffer,sizeof(int));
		recvd=recv(client_sock,buffer,lenCadena,MSG_WAITALL);
		if(recvd<=0)
		{
			if(recvd==-1)
			{
				perror("recv");
			}
			printf("Ha ocurrido un error con el socket %d y ha sido desconectado \n",client_sock);
			close(client_sock);
			break;
		}

		printf("Ha recibido del servidor el siguiente mensaje: %s \n",buffer);
	}
	free(serverAddress);
	free(localAddress);
	return NULL;
}

void Comunicarse()
{
	sem_wait(&semConexion);
	char* cadena= malloc(MAX_BUFFER_SIZE);
	printf("Cliente listo para recibir mensajes por consola\n");
	while(fgets(cadena,MAX_BUFFER_SIZE,stdin) != NULL)
	{
		char* mensaje=malloc(sizeof(int)+strlen(cadena)+1);
		int len=strlen(cadena)+1;
		int tmpSize=0;
		memcpy(mensaje,&len,tmpSize= sizeof(int));
		memcpy(mensaje+tmpSize,cadena,strlen(cadena)+1);

		if(send(client_sock,mensaje,len+tmpSize,MSG_NOSIGNAL) <=0)
			close(client_sock);
	}

	if(cadena != NULL)
		free(cadena);
}



