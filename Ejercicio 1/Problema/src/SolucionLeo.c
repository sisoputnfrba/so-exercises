/*
 * Ejercicio1.c
 *
 *  Created on: 07/03/2012
 *      Author: sebastian
 */

#include "SolucionLeo.h"
#define SALDO 500
int saldoInicial=SALDO;

int main (void)
{
	pthread_t  h1,h2; //Estructuras que representan un "Handle" al hilo, nos permite luego por ejemplo joinear el hilo.
	pthread_create(&h1,NULL,ComprasMensuales,"Julieta");
	pthread_create(&h2,NULL,ComprasMensuales,"Leo");
	pthread_join(h1,(void **)NULL);//El hilo principal (main) se bloquea hasta que el hilo h1 finalice
	pthread_join(h2,(void **)NULL);

	return EXIT_SUCCESS;
}
/**/
void* ComprasMensuales(void * args)
{
	char* nombre=(char*)args;

	for(int i=0; i< (SALDO/10);i++ )
	{
		 HacerCompras(10,nombre);
		 if(ConsultaSaldo()<0)
			 printf("La cuenta esta en rojo!! El almacenero nos va a matar!\n");
	}

	return NULL;
}

int ConsultaSaldo()
{
	return saldoInicial;
}

void HacerCompras(int monto,const char* nombre)
{
	if(ConsultaSaldo()>=monto)
	{
		printf("Hay saldo suficiente %s esta por comprar.\n", nombre);
		usleep(1);
		Comprar(monto);
		printf("%s acaba de comprar.\n",nombre);
	}
	else
		printf("No queda suficiente saldo (%d)  para que %s haga las compras.\n",ConsultaSaldo(),nombre);
	usleep(1);
}

void Comprar(int monto)
{
	saldoInicial=saldoInicial-monto;
}
