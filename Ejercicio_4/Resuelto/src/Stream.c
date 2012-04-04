/*
 * Stream.c
 *
 *  Created on: Apr 3, 2012
 *      Author: shinichi
 */


#include "Stream.h"

#include <stdlib.h>

t_stream* t_stream_create(int size) {
	t_stream* stream = malloc(sizeof(t_stream));
	stream->size = size;
	stream->data = malloc(size);
	return stream;
}

void t_stream_destroy(t_stream* stream) {
	free(stream->data);
	free(stream);
}
