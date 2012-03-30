/*
 * Ejercicio4.c
 *
 *  Created on: 11/03/2012
 *      Author: sebastian
 */

#include "Ejercicio4.h"

/*
 * Por una cuestion de simplicidad del ejercicio
 * el stream resultante de la serializacion es grabado a un archivo
 * Si se reemplazaran los write, por send y los read por recv
 * se puede usar para armar un protocolo de comunicacion simple
 * en el que podemos enviar estructuras complejas.
 */

const char* letras="ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
int main(void)
{
	t_Spock* spock= t_Spock_CrearSpock();
	t_Spock_EnviarAMision(spock);
	return EXIT_SUCCESS;
}

t_Spock* t_Spock_CrearSpock()
{
	t_Spock* spock=malloc(sizeof(t_Spock));
	spock->edad=40;
	spock->nombre=malloc(strlen("Roberto Spock")+1);
	strcpy(spock->nombre,"Roberto Spock");

	spock->mascota=malloc(sizeof(t_mascota));
	spock->mascota->apodo=malloc(strlen("Babu")+1);
	strcpy(spock->mascota->apodo, "Babu");
	spock->mascota->daVueltas=true;
	spock->mascota->edad=5;
	spock->listaDeVillanos=list_create();
	t_Villano* villano;
	villano=malloc(sizeof(t_Villano));
	villano->edad=34;
	memset(villano->nombre,'\0',sizeof(villano->nombre));
	strcpy(villano->nombre,"Borg Queen");
	list_add(spock->listaDeVillanos,villano);
	villano=malloc(sizeof(t_Villano));
	villano->edad=20;
	memset(villano->nombre,'\0',sizeof(villano->nombre));
	strcpy(villano->nombre,"Locotus");
	list_add(spock->listaDeVillanos,villano);
	villano=malloc(sizeof(t_Villano));
	villano->edad=67;
	memset(villano->nombre,'\0',sizeof(villano->nombre));
	strcpy(villano->nombre,"Dukat");
	list_add(spock->listaDeVillanos,villano);

	int random;
	do
		{
		 random=rand();
		}while(random<0);
		char* mensaje=malloc(random % strlen(letras));
		for (int i=0;i<(random % strlen(letras));i++)
		{
			int num=rand();

			if((num % strlen(letras))>0 && (num % strlen(letras)) <random)
				mensaje[i]=letras[(num % strlen(letras))];
			else
				mensaje[i]=letras[i];

		}
	mensaje[(random % strlen(letras)) -1] = '\0';
	spock->mision=malloc(sizeof(t_mision));
	spock->mision->informacionCodificada=mensaje;
	spock->mision->longitudInformacionCodificada=random % strlen(letras);
	return spock;
}

void t_Spock_Destruir(t_Spock* spock)
{
	free(spock->nombre);
	free(spock->mascota->apodo);
	free(spock->mascota);
	free(spock->mision->informacionCodificada);
	free(spock->mision);
	list_destroy_and_destroy_elements(spock->listaDeVillanos,t_Villano_Destroyer);

	free(spock);
}

void t_Villano_Destroyer(void* villano)
{
	free(villano);
}

void t_Spock_EnviarAMision(t_Spock* spock)
{
	struct stat statSpock;
	FILE* file=fopen("./spock.bin","w");
	fwrite(spock,sizeof(t_Spock),1,file);
	fflush(file);
	t_Spock* spockRecibido= malloc(sizeof(t_Spock));
	stat("./spock.bin",&statSpock);
	fread(spockRecibido,statSpock.st_size,1,file);

	//1° Metodo de comparacion: Comparar los streams
	if(memcmp(spock, spockRecibido,statSpock.st_size) != 0)
	{
		printf("Los spock son distintos!!\n");
	}
	//2° Metodo, comparar las estructuras campo por campo
	t_Spock_CompararSpocks(spock,spockRecibido);

}


void t_Spock_CompararSpocks(t_Spock* spockEnviado,t_Spock* spockRecibido)
{

	printf("Edad Spock original: %d Edad Spock Nuevo %d \n",spockEnviado->edad,spockRecibido->edad);
	printf("Nombre Spock original: %s Nombre Spock Nuevo %s \n",spockEnviado->nombre,spockRecibido->nombre);
	printf("Apodo mascota Spock original: %s Apodo mascota Spock Nuevo %s \n",spockEnviado->mascota->apodo,spockRecibido->mascota->apodo);
	printf("Da Vueltas mascota Spock original: %s Da Vueltas mascota Spock Nuevo %s \n",(spockEnviado->mascota->daVueltas)?"true":"false",(spockRecibido->mascota->daVueltas)?"true":"false");
	printf("Edad mascota Spock original: %d Edad mascota Spock Nuevo %d \n",spockEnviado->mascota->edad,spockRecibido->mascota->edad);
	printf("Informacion codificada Spock original: %s Informacion Codificada Spock Nuevo %s \n",spockEnviado->mision->informacionCodificada,spockRecibido->mision->informacionCodificada);
	printf("Longitud Informacion codificada Spock original: %d Edad Spock Nuevo %d \n",spockEnviado->mision->longitudInformacionCodificada,spockEnviado->mision->longitudInformacionCodificada);
	list_iterate(spockEnviado->listaDeVillanos,  ChequearVillanos);
	list_iterate(spockRecibido->listaDeVillanos, ChequearVillanos);
}

void ChequearVillanos(void* villano)
{
	t_Villano* v=villano;
	printf("Edad villano %d\n",v->edad);
	printf("Nombre villano %s\n",v->nombre);



}
