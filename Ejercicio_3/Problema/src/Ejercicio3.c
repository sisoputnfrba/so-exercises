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

#include "Ejercicio3.h"

t_hamburguesa hamburgesa;

int main (void)
{
	pthread_t h1,h2,h3,h4,h5,h6,h7,h8;
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
	Agregar(PANINFERIOR);
	return NULL;
}

void*  Agregar_Condimento (void * args)
{
	Agregar(CONDIMENTOS);
	return NULL;
}

void*  Agregar_Carne (void * args)
{
	Agregar(CARNE);
	return NULL;
}

void*  Agregar_Queso (void * args)
{
	Agregar(QUESO);
	return NULL;
}

void*  Agregar_Panceta (void * args)
{
	Agregar(PANCETA);
	return NULL;
}

void*  Agregar_Lechuga (void * args)
{
	Agregar(LECHUGA);
	return NULL;
}

void*  Agregar_Tomate (void * args)
{
	Agregar(TOMATE);
	return NULL;
}

void*  Agregar_Pan_Superior (void * args)
{
	Agregar(PANSUPERIOR);
	return NULL;
}


void*  Entregar (void * args)
{
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
/*Esta correctamente armada si tiene todos los ingredientes,
 *  y los tiene definidos en el orden dado por el enum t_Ingredientes*/

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
