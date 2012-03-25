/*
 * Ejercicio5.c
 *
 *  Created on: 11/03/2012
 *      Author: sebastian
 */
#include "Ejercicio6.h"
#define MAX_BUFFER_SIZE  200

int port;


/*
 * Para evitar el uso de un socket global, se podria implementar una cola de mensajes
 * entre el hilo que recibe de consola y el hilo de comunicaciones asi este es el unico que se relaciona con el socket
 * Para esto es necesario aplicarle locks al TAD de queue actual.
 */
int main (int argc, char* argv[])
{
	if(argc!= 2)
	{
		printf("Cantidad invalida de argumentos, debe ingresar el puerto como parametro!\n");
		return EXIT_FAILURE;
	}
	port=atoi(argv[1]);
	IniciarConexion();
	return EXIT_SUCCESS;
}

void IniciarConexion()
{
	fd_set setMaster,setCopia;

	char buffer[MAX_BUFFER_SIZE];
	int server_sock=socket(AF_INET,SOCK_STREAM,0);
	unsigned int len=sizeof(struct sockaddr);
	int yes=0;
	if(setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &yes,  sizeof(int))==-1)
		perror("setsockopt");
	struct sockaddr_in* localAddress= malloc(sizeof(struct sockaddr_in));
	struct sockaddr_in* serverAddress= malloc(sizeof(struct sockaddr_in));
	localAddress->sin_addr.s_addr=inet_addr("127.0.0.1");
	localAddress->sin_port=htons(port);
	localAddress->sin_family=AF_INET;
	if(bind(server_sock,(struct sockaddr*)localAddress,(socklen_t)sizeof(struct sockaddr_in))==-1)
		perror("bind");

	if(listen(server_sock,10)==-1)
		perror("listen");

	FD_ZERO(&setMaster);
	FD_SET(server_sock,&setMaster);

	int descriptorMasAlto=server_sock;
	printf("Servidor listo para escuchar conexiones\n");
	while(true)
	{
		setCopia=setMaster;
		int i=select(descriptorMasAlto+1,&setCopia,NULL,NULL,NULL);
		if(i==-1)
		{
			perror("select");
			break;
		}

		int nDescriptor=0;
		while(nDescriptor<=descriptorMasAlto)
		{
			if(FD_ISSET(nDescriptor,&setCopia))
			{
				if(nDescriptor==server_sock)
				{
					int client_sock;
					if((client_sock= accept(server_sock,(struct sockaddr*)serverAddress,&len))==-1)
					{
						printf("El socket %d ha producido un error y ha sido desconectado.\n",client_sock);
						perror("accept");
						nDescriptor++;
						continue;
					}
					printf("El socket %d se ha conectado al servidor.\n",client_sock);
					FD_SET(client_sock,&setMaster);
					if(client_sock > descriptorMasAlto)
						descriptorMasAlto=client_sock;

				}
				else
				{
					memset(buffer,'\0',MAX_BUFFER_SIZE);
					int recvd=recv(nDescriptor,buffer,sizeof(int),MSG_WAITALL);
					if(recvd<=0)
					{
						if(recvd==-1)
						{
							perror("recv");
						}
						printf("El socket %d ha producido un error y ha sido desconectado.\n",nDescriptor);
						close(nDescriptor);
						FD_CLR(nDescriptor,&setMaster);
						nDescriptor++;
						continue;
					}

					int lenCadena;
					memcpy(&lenCadena,buffer,sizeof(int));
					recvd=recv(nDescriptor,buffer,lenCadena,MSG_WAITALL);
					if(recvd<=0)
					{
						if(recvd==-1)
						{
							perror("recv");
						}
						printf("El socket %d ha producido un error y ha sido desconectado.\n",nDescriptor);
						close(nDescriptor);
						FD_CLR(nDescriptor,&setMaster);
						nDescriptor++;
						continue;
					}


					printf("Ha recibido del cliente el siguiente mensaje: %s  \n",buffer);

					for(int j = server_sock; j <= descriptorMasAlto; j++)
					{
						if (j != server_sock && j != nDescriptor)
						{
							char* mensaje=malloc(sizeof(int)+lenCadena);
							int len=lenCadena;
							int tmpSize=0;
							memcpy(mensaje,&len,tmpSize= sizeof(int));
							memcpy(mensaje+tmpSize,buffer,lenCadena);
							printf("Enviando mensaje %s al socket %d", mensaje,j);
							if(send(j,mensaje,len+tmpSize,MSG_NOSIGNAL) <=0)
								{
									printf("El socket %d ha producido un error y ha sido desconectado.\n",j);
									close(j);
									FD_CLR(j,&setMaster);
								}

							free(mensaje);
						}
					}
				}
			}

			nDescriptor++;
		}


	}



	free(serverAddress);
	free(localAddress);

}

