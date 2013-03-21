//Mihai Neacsu 331CA
//SO Tema 0

#ifndef LIST_H_
#define LIST_H_

#include <stdio.h>

typedef struct nod{
	struct nod *next;
	struct nod *prev;
	void *data;
} *Nod;

typedef struct nod *List_Iter;

typedef struct list{
	Nod head;
	Nod last;
} *List;

List new_List();
void delete_List(List L);
void increase_List(List L);
void append_List(List L, const void *data);
int isEmpty_List(List L);
void * getElem_List(List L, List_Iter it);
List_Iter find_List(List L, const void * toFind);
void removeNod_List(List L, List_Iter toRemove);
void removeElem_List(List L, const void * toRemove);
void clear_List(List L);
void print_List(List L, FILE * stream);

List_Iter begin_List(List L);
List_Iter end_List(List L);
List_Iter prev_List(List L, List_Iter current);
List_Iter next_List(List L, List_Iter current);

#endif
