/*
 * Ejercicio7.c
 *
 *  Created on: Mar 25, 2012
 *      Author: seba
 */

#include "Ejercicio7.h"
int main(void)
{
	Error1();
	Error2();
	Error3();
	Error4();
	Error6();
	printf("Pareciera que esta todo bien!!\n");
}
void Error1()
{
	printf("Error 1 \n");
	int i;
	char cadena[10];
	char cadena2[10];
	for( i=1;i<=10;i++)
	{
		switch(i)
		{
			case 1:
				cadena[i]='A';
			case 2:
				cadena[i]='B';
			case 3:
				cadena[i]='C';
			case 4:
				cadena[i]="D";
			default:
				cadena[i]="-";

		}
	}
	cadena[9]='a';
	printf("cadena 1: %s",cadena);
	if(strcmp(cadena2,cadena))
		printf("Genere 2 cadenas iguales!\n");


}

void Error2()
{
	char* cadena1="El Zumba";
	char* cadena2="El Zumba";
	if(cadena1==cadena2)
		printf("Son iguales! :)\n");
	char * st;
	strcpy(st, "abc");
	char* cadena3=malloc(strlen(cadena1));
	strcpy(cadena3,cadena1);
	strcpy(cadena2,cadena3);
	if(strcmp(cadena1,cadena2)==0)
		printf("Genere 2 cadenas iguales!\n");
}

void Error3()
{
	int x;
	char * st = malloc(31);

	scanf("Inserte un numero %d\n", x);
	scanf("Inserte una cadena %30s\n", &st);
	char* st2=st;
	ModificarCadena(st);
	if(strcmp(st,st2) !=0)
		printf("Logre cambiar la cadena! \n");
	else
		printf("No logre cambiar la cadena! \n");
}

void ModificarCadena(char* st)
{
	st="Nueva Cadena";
}
void Error4()
{
	double raiz=sqrt(16);
	if(raiz > 1)
		printf("Yuppiiie estoy para aprobar AM2!!\n");
		Error5(raiz);
		if(raiz == 2)
			printf("Yuppiiie estoy para aprobar SO!!\n");
	else
		printf("La raiz de 2 no me dio menor a 1!!!");
}

void Error5(double raiz)
{
	raiz=pow(raiz,2);
}

void Error6()
{
	int x = 5;
	while( x > 0 );
		x--;
}
