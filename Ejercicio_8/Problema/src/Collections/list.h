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

#ifndef LIST_H_
#define LIST_H_

	#include "node.h"
	#include "stdbool.h"

	typedef struct {
		t_link_element *head;
		int elements_count;
	} t_list;

	t_list * list_create();

	void list_destroy(t_list *);
	void list_destroy_and_destroy_elements(t_list*, void(*element_destroyer)(void*));

	int list_add(t_list *, void *element);
	void list_add_in_index(t_list *, int index, void *element);

	void *list_get(t_list *, int index);

	void *list_replace(t_list*, int index, void* element);
	void list_replace_and_destroy_element(t_list*, int index, void* element, void(*element_destroyer)(void*));

	void *list_remove(t_list *, int index);
	void list_remove_and_destroy_element(t_list *, int index, void(*element_destroyer)(void*));

	void *list_remove_by_condition(t_list *, bool(*condition)(void*));
	void list_remove_and_destroy_element_by_condition(t_list *, bool(*condition)(void*), void(*element_destroyer)(void*));

	void list_clean(t_list *);
	void list_clean_and_destroy_elements(t_list *self, void(*element_destroyer)(void*));

	void list_iterate(t_list *, void(*closure)(void*));
	void *list_find(t_list *, bool(*closure)(void*));

	int list_size(t_list *);
	int list_is_empty(t_list *);

#endif /*LIST_H_*/

