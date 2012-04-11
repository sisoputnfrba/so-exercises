/*
 * Factura.c
 *
 *  Created on: Apr 10, 2012
 *      Author: shinichi
 */

#include "Factura.h"

#include <stdlib.h>

t_factura* factura_crear(char numero, t_factura_tipo tipo,
		t_cliente* cliente, double total){
	t_factura* factura = malloc(sizeof(t_factura));
	factura->numero = numero;
	factura->cliente = cliente;
	factura->tipo = tipo;
	factura->total = total;
	factura->items = list_create();
	return factura;
}

void factura_destroy(t_factura* factura) {
	list_destroy_and_destroy_elements(factura->items, (void*) item_destroy);
	cliente_destroy(factura->cliente);
	free(factura);
}

void factura_add_item(t_factura* factura, t_item* item) {
	list_add(factura->items, item);
}

void factura_print(t_factura* factura) {
	int i = 0;
	void print_item(void* element) {
		t_item* item = element;
		i++;
		printf("Item %d Nombre: %s\n", i, item->nombre);
		printf("Item %d Precio: %lf\n", i, item->precio);
	}

	printf("#########\n");
	printf("FACTURA\n");
	printf("#########\n");
	printf("Numero: %d\n", factura->numero);
	printf("Tipo: %u\n", factura->tipo);
	printf("Cliente Codigo: %d\n", factura->cliente->codigo_cliente);
	printf("Cliente Nombre: %s, %s\n", factura->cliente->apellido, factura->cliente->nombre);
	list_iterate(factura->items, print_item);
	printf("Total: %lf\n", factura->total);
}

t_factura* factura_from_file(FILE* file) {
	char numero = 0;
	t_factura_tipo tipo;
	double total;
	int cantidad_items;
	t_cliente* cliente;
	t_item* item;
	int i;

	fscanf(file, "%d,%u,%lf,%d\n", &numero, &tipo, &total, &cantidad_items);
	cliente = cliente_from_file(file);
	t_factura* factura = factura_crear(numero, tipo, cliente, total);

	for (i = 0; i < cantidad_items; ++i) {
		item = item_from_file(file);
		factura_add_item(factura, item);
	}

	return factura;
}
