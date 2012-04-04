/*
 * Stream.h
 *
 *  Created on: Apr 3, 2012
 *      Author: shinichi
 */

#ifndef STREAM_H_
#define STREAM_H_

typedef struct {
	char* data;
	int size;
} t_stream;

t_stream* t_stream_create(int size);
void t_stream_destroy(t_stream* stream);


#endif /* STREAM_H_ */
