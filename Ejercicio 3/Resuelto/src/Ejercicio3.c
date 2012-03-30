/*
 * Ejercicio3Resuelto.c
 *
 *  Created on: 10/03/2012
 *      Author: sebastian
 */

#include "Ejercicio3.h"

t_hamburguesa hamburgesa;
sem_t semPanInferior;
sem_t semCondimento;
sem_t semCarne;
sem_t semQueso;
sem_t semPanceta;
sem_t semLechuga;
sem_t semTomate;
sem_t semPanSuperior;
sem_t semEntrega;

int main (void)
{
	pthread_t h1,h2,h3,h4,h5,h6,h7,h8;

	sem_init(&semPanInferior,0,1);
	sem_init(&semCondimento,0,0);
	sem_init(&semCarne,0,0);
	sem_init(&semQueso,0,0);
	sem_init(&semPanceta,0,0);
	sem_init(&semLechuga,0,0);
	sem_init(&semTomate,0,0);
	sem_init(&semPanSuperior,0,0);
	sem_init(&semEntrega,0,0);

	hamburgesa.embalada=false;
	hamburgesa.ingredientes=queue_create();

	pthread_create(&h1,NULL,Agregar_Pan_Inferior,NULL);
	pthread_create(&h2,NULL,Agregar_Condimento,NULL);
	pthread_create(&h3,NULL,Agregar_Carne,NULL);
	pthread_create(&h4,NULL,Agregar_Queso,NULL);
	pthread_create(&h5,NULL,Agregar_Panceta,NULL);
	pthread_create(&h6,NULL,Agregar_Lechuga,NULL);
	pthread_create(&h7,NULL,Agregar_Tomate,NULL);
	pthread_create(&h7,NULL,Agregar_Pan_Superior,NULL);
	pthread_create(&h8,NULL,Entregar,NULL);

	pthread_join(h1,(void**)NULL);
	pthread_join(h2,(void**)NULL);
	pthread_join(h3,(void**)NULL);
	pthread_join(h4,(void**)NULL);
	pthread_join(h5,(void**)NULL);
	pthread_join(h6,(void**)NULL);
	pthread_join(h7,(void**)NULL);
	pthread_join(h8,(void**)NULL);

	return EXIT_SUCCESS;
}

void*  Agregar_Pan_Inferior (void * args)
{
	sem_wait(&semPanInferior);
	Agregar(PANINFERIOR);
	sem_post(&semCondimento);
	return NULL;
}


void*  Agregar_Condimento (void * args)
{
	sem_wait(&semCondimento);
	Agregar(CONDIMENTOS);
	sem_post(&semCarne);
	return NULL;
}

void*  Agregar_Carne (void * args)
{
	sem_wait(&semCarne);
	Agregar(CARNE);
	sem_post(&semQueso);
	return NULL;
}

void*  Agregar_Queso (void * args)
{
	sem_wait(&semQueso);
	Agregar(QUESO);
	sem_post(&semPanceta);
	return NULL;
}

void*  Agregar_Panceta (void * args)
{
	sem_wait(&semPanceta);
	Agregar(PANCETA);
	sem_post(&semLechuga);
	return NULL;
}

void*  Agregar_Lechuga (void * args)
{
	sem_wait(&semLechuga);
	Agregar(LECHUGA);
	sem_post(&semTomate);
	return NULL;
}

void*  Agregar_Tomate (void * args)
{
	sem_wait(&semTomate);
	Agregar(TOMATE);
	sem_post(&semPanSuperior);
	return NULL;
}

void*  Agregar_Pan_Superior (void * args)
{
	sem_wait(&semPanSuperior);
	Agregar(PANSUPERIOR);
	sem_post(&semEntrega);
	sem_post(&semPanInferior);

	return NULL;
}



void*  Entregar (void * args)
{

	sem_wait(&semEntrega);
	if(!EstaBienArmada())
		printf("Error en el armado de la hamburguesa!! El cliente se fue a comerse un triple bacon a mc :( \n");
	else
		printf("Hamburguesa armada perfectamente!! Le hemos tapado 5 arterias al cliente!! :)\n");
	return NULL;
}

void Agregar(t_Ingredientes ingrediente)
{
	printf("Agregando ingrediente %s\n", Ingrediente_ToString(ingrediente));
	int * i= malloc(sizeof(int));
	*i=ingrediente;
	queue_push(hamburgesa.ingredientes,i);
}

int EstaBienArmada()
{

	for (int i=0; (((t_Ingredientes)i) != FIN) ; i++)
	{
		t_Ingredientes ingredienteCorrecto=(t_Ingredientes)i;
		t_Ingredientes ingredienteHamburguesa;
		int * ingrediente=queue_pop(hamburgesa.ingredientes);

		if(ingrediente==NULL)
		{
			printf("Faltaron ingredientes!\n");
			return 0;
		}
		else
		{
			ingredienteHamburguesa=(t_Ingredientes)*ingrediente;
			return ingredienteHamburguesa==ingredienteCorrecto;
		}
	}

	return 0;
}

char* Ingrediente_ToString(t_Ingredientes ingrediente)
{
	char* ingredienteChar;
	switch(ingrediente)
	{
		case PANINFERIOR:
			ingredienteChar="PANINFERIOR";
			break;
		case PANSUPERIOR:
				ingredienteChar="PANSUPERIOR";
			break;
		case CARNE:
			ingredienteChar="CARNE";
			break;
		case QUESO:
			ingredienteChar="QUESO";
			break;
		case PANCETA:
			ingredienteChar="PANCETA";
			break;
		case LECHUGA:
			ingredienteChar="LECHUGA";
			break;
		case TOMATE:
			ingredienteChar="TOMATE";
			break;
		case CONDIMENTOS:
			ingredienteChar="CONDIMENTOS";
			break;
		default:
			ingredienteChar="Desconocido!";
			break;

	}

	return ingredienteChar;

}
