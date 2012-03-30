/*
 * Ejercicio4Resuelto.c
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
	t_Spock_Destruir(spock);
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
	t_stream* streamEnviado=t_Spock_Serialize(spock);
	FILE* file=fopen("./spock.bin","w");
	fwrite(streamEnviado->data,streamEnviado->length,1,file);
	fflush(file);
	fclose(file);

	file=fopen("./spock.bin","r");
	t_stream* streamRecibido= malloc(sizeof(t_stream));
	stat("./spock.bin",&statSpock);
	streamRecibido->length=statSpock.st_size;
	streamRecibido->data=malloc(statSpock.st_size);
	fread(streamRecibido->data,statSpock.st_size,1,file);

	//1° Metodo de comparacion: Comparar los streams
	if(memcmp(streamEnviado->data, streamRecibido->data,statSpock.st_size) != 0)
	{
		printf("Los spock son distintos!!");
	}

	t_Spock* spockRecibido=t_Spock_Deserialize(streamRecibido);
	free(streamRecibido->data);
	free(streamRecibido);
	free(streamEnviado->data);
	free(streamEnviado);

	//2° Metodo, comparar las estructuras campo por campo
	t_Spock_CompararSpocks(spock,spockRecibido);

	t_Spock_Destruir(spockRecibido);

}

t_stream* t_Spock_Serialize(t_Spock* spock)
{
	int offset=0,tmpSize=0;
	t_stream* stream=malloc(sizeof(t_stream));
	stream->length=strlen(spock->nombre)+1+sizeof(int)+
			+sizeof(int)+spock->mision->longitudInformacionCodificada+
			strlen(spock->mascota->apodo)+1+sizeof(bool)+sizeof(int)+
			list_size(spock->listaDeVillanos)*sizeof(t_Villano);
	stream->data=malloc(stream->length);

	memcpy(stream->data,spock->nombre,tmpSize= strlen(spock->nombre)+1);
	offset=tmpSize;

	memcpy(stream->data+offset,&spock->edad,tmpSize= sizeof(int));
	offset+=tmpSize;

	memcpy(stream->data+offset,&spock->mision->longitudInformacionCodificada,tmpSize=sizeof(int));
	offset+=tmpSize;

	memcpy(stream->data+offset,spock->mision->informacionCodificada,tmpSize=spock->mision->longitudInformacionCodificada);
	offset+=tmpSize;

	memcpy(stream->data+offset,spock->mascota->apodo,tmpSize=strlen(spock->mascota->apodo)+1);
	offset+=tmpSize;

	memcpy(stream->data+offset,&spock->mascota->daVueltas,tmpSize=sizeof(bool));
	offset+=tmpSize;

	memcpy(stream->data+offset,&spock->mascota->edad,tmpSize=sizeof(int));
	offset+=tmpSize;

	t_stream* streamVillanos=t_list_serialize(spock->listaDeVillanos,t_villano_serialize);

	memcpy(stream->data+offset,streamVillanos->data,tmpSize=streamVillanos->length);
	free(streamVillanos->data);
	free(streamVillanos);

	return stream;
}

t_stream* t_villano_serialize(void* elem)
{
	t_stream* stream =malloc(sizeof(t_stream));
	t_Villano* villano=elem;
	stream->data=malloc(sizeof(t_Villano)); //Esto es valido pq t_Villano NO TIENE CAMPOS DINAMICOS
	memcpy(stream->data,villano,sizeof(t_Villano));
	stream->length=sizeof(t_Villano);
	return stream;
}




t_stream* t_list_serialize(t_list* list, t_stream* (*closure)(void*))
{
	t_link_element *element = list->head;
	t_stream* streamToSend= malloc(sizeof(t_stream));
	streamToSend->data=NULL;
	streamToSend->length=0;
	while (element != NULL)
	{
		t_stream* stream=closure(element->data);
		int sizeAnterior=streamToSend->length;
		if(sizeAnterior != 0)
		{
			void* data= malloc(sizeAnterior);
			memcpy(data,streamToSend->data,sizeAnterior);//Guardo una copia del stream->data
			if(streamToSend->data != NULL)
				free(streamToSend->data);
			streamToSend->data=malloc(sizeAnterior+stream->length);//Re alocamos memoria para agrandar el stream->data
			streamToSend->length=sizeAnterior+stream->length;
			memcpy(streamToSend->data,data,sizeAnterior);//Copio el data original
			free(data);
		}
		else
		{
			if(streamToSend->data != NULL)
				free(streamToSend->data);
			streamToSend->data=malloc(stream->length);//Re alocamos memoria para agrandar el stream->data
			streamToSend->length=stream->length;
		}
		//Copio al final del stream original, lo que resulto de la serializacion
		memcpy(streamToSend->data+sizeAnterior,stream->data,stream->length);
		free(stream->data);
		free(stream);
		element = element->next;
	}

	return streamToSend;
}



t_Spock* t_Spock_Deserialize(t_stream* stream)
{
	/*strlen(spock->nombre)+1+sizeof(int)+
	spock->mision->longitudInformacionCodificada+
	strlen(spock->mascota->apodo)+1+sizeof(bool)+sizeof(int)+
	list_size(spock->listaDeVillanos)*sizeof(t_Villano);*/
	t_Spock* spock= malloc(sizeof(t_Spock));
	int offset=0,tmpSize=0;

	for(tmpSize=1;(stream->data+offset)[tmpSize-1] != '\0';tmpSize++)
		;
	spock->nombre=malloc(tmpSize);
	memcpy(spock->nombre,stream->data+offset,tmpSize);
	offset+=tmpSize;

	memcpy(&spock->edad,stream->data+offset,tmpSize=sizeof(int));
	offset+=tmpSize;

	spock->mision=malloc(sizeof(t_mision));
	memcpy(&spock->mision->longitudInformacionCodificada,stream->data+offset,tmpSize=sizeof(int));
	offset+=tmpSize;

	spock->mision->informacionCodificada=malloc(spock->mision->longitudInformacionCodificada);
	memcpy(spock->mision->informacionCodificada,stream->data+offset,tmpSize=spock->mision->longitudInformacionCodificada);
	offset+=tmpSize;

	spock->mascota=malloc(sizeof(t_mascota));
	for(tmpSize=1;(stream->data+offset)[tmpSize-1] != '\0';tmpSize++)
			;
	spock->mascota->apodo=malloc(tmpSize);
	memcpy(spock->mascota->apodo,stream->data+offset,tmpSize);
	offset+=tmpSize;

	memcpy(&spock->mascota->daVueltas,stream->data+offset,tmpSize=sizeof(bool));
	offset+=tmpSize;

	memcpy(&spock->mascota->edad,stream->data+offset,tmpSize=sizeof(int));
	offset+=tmpSize;

	t_stream* streamVillano=malloc(sizeof(t_stream));
	streamVillano->length=stream->length-offset;
	streamVillano->data=malloc(streamVillano->length);
	void* data=streamVillano->data; //Para poder liberar la memoria de la DATA ya que adentro del serialize se va moviendo el puntero del stream
	memcpy(streamVillano->data,stream->data+offset,streamVillano->length);
	spock->listaDeVillanos=t_list_deserialize(streamVillano,t_Villano_deserialize);
	free(data);
	free(streamVillano);

	return spock;
}

t_list* t_list_deserialize(t_stream* stream, void* (*closure)(t_stream*))
{
	t_list* list=list_create();
	while (stream->length>0)
	{
		/*
		 * Para el correcto funcionamiento el closure DEBE modificar el stream ejecucion a ejecucion
		 * Actualizando el data que se va quitando y el length,
		 * de lo contrario la condicion de corte nunca se daria
		 */
		void* elem=closure(stream);
		list_add(list,elem);
	}

	return list;
}

void* t_Villano_deserialize(t_stream* stream)
{
	int tmpSize=0;
	stream->length-=sizeof(t_Villano);
	t_Villano* villano=malloc(sizeof(t_Villano));
	memcpy(villano,stream->data,tmpSize=sizeof(t_Villano));
	stream->data=stream->data+tmpSize;
	return villano;

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
