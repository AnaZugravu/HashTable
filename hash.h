//Mihai Neacsu 331CA
//SO Tema 0

#ifndef HASH_H_
#define HASH_H_

#include "list.h"
#include <stdio.h>

typedef struct hashmap{
	unsigned int length;
	List *lists;
} *Hash;

Hash new_Hash(int length);
void add_Hash(Hash H, const void *toAdd);
void remove_Hash(Hash H, const void *toRemove);
void clear_Hash(Hash H);
void delete_Hash(Hash H);
int find_Hash(Hash H, const void * toFind);
void printBucket_Hash(Hash H, unsigned int index, FILE * stream);
void print_Hash(Hash H, FILE * stream);
Hash resize_Hash(Hash H, unsigned int newLength);
void resizeDouble_Hash(Hash *H);
void resizeHalve_Hash(Hash *H);

unsigned int hash(const char *str, unsigned int hash_length);

#endif
