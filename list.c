//Mihai Neacsu 331CA
//SO Tema 0

#include "list.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

List new_List(){
	List newList;
	
	newList = malloc(sizeof(struct list));
	newList->head = NULL;
	newList->last = NULL;

	return newList;
}

void delete_List(List L){
	clear_List(L);

	free(L);
}

void clear_List(List L){
	List_Iter crnt, next;
	crnt = begin_List(L);

	while (crnt != end_List(L)){
		next = next_List(L, crnt);
		removeNod_List(L, crnt);
		crnt = begin_List(L);
	}
}

void increase_List(List L){
	Nod newNod;
	assert(L);

	newNod = malloc(sizeof(struct nod));
	newNod->prev = L->last;
	newNod->next = NULL;

    if (isEmpty_List(L))
		L->head = newNod;
	else
		L->last->next = newNod;

	L->last = newNod;
}

void append_List(List L, const void *data){
	assert(L && data);

	if (find_List(L, data))
		return;
	
	increase_List(L);
	
	L->last->data = malloc(strlen((char *)data) + 1);
	strcpy(L->last->data, data);
}

int isEmpty_List(List L){
	assert(L);

	return !L->head;
}

void * getElem_List(List L, List_Iter it){
	assert(L && !isEmpty_List(L) && it);

	return it->data;
}

List_Iter find_List(List L, const void * toFind){
	List_Iter it;
	if (!L)
		return NULL;

	it = begin_List(L);
	while (it != end_List(L)){
		if (strcmp(toFind, getElem_List(L, it)) == 0)
			break;

		it = next_List(L, it);
	}

	return it;
}

void removeNod_List(List L, List_Iter toRemove){
	assert(L && !isEmpty_List(L) && toRemove);

	if (toRemove == L->last)
		L->last = prev_List(L, toRemove);

	if (prev_List(L, toRemove))	
		prev_List(L, toRemove)->next = next_List(L, toRemove);

	if (next_List(L, toRemove))
		next_List(L, toRemove)->prev = prev_List(L, toRemove);

	if (toRemove == begin_List(L))
		L->head = next_List(L, toRemove);

	free(toRemove->data);
	free(toRemove);
}

void removeElem_List(List L, const void * toRemove){
	List_Iter it;
	assert(L && toRemove);

	it = find_List(L, toRemove);
	if (it)
		removeNod_List(L, it);
}

void print_List(List L, FILE * stream){
	List_Iter it;
	assert(L && stream);
	
	it = begin_List(L);
	while (it != end_List(L)){
		fputs(getElem_List(L, it), stream);
		
		it = next_List(L, it);

		if (it)
			fputs(" ", stream);
	}
	
	fputs("\n", stream);
	fflush(stream); //sa ne asiguram ca se goleste bufferul
}

List_Iter begin_List(List L){
	assert(L);

	return L->head;
}

List_Iter end_List(List L){
	assert(L);

	return NULL;
}

List_Iter prev_List(List L, List_Iter crnt){
	assert(L && !isEmpty_List(L) && crnt);

	return crnt->prev;
}

List_Iter next_List(List L, List_Iter crnt){
	assert(L && !isEmpty_List(L) && crnt);

	return crnt->next;
}
