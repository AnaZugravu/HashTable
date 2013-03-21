//Mihai Neacsu 331CA
//SO Tema 0

#include "hash.h"
#include <stdlib.h>
#include <assert.h>

Hash new_Hash(int length){
	Hash newHash;
	int i;
	
	newHash = malloc(sizeof(struct hashmap));
	newHash->length = length;
	newHash->lists = calloc(length, sizeof(struct list *));

	for (i = 0; i < length; ++i)
		newHash->lists[i] = new_List();

	return newHash;
}

void add_Hash(Hash H, const void *toAdd){
	unsigned int value;
	assert(H && toAdd);

	value = hash((char *)toAdd, H->length);
	append_List(H->lists[value], toAdd);
}

void remove_Hash(Hash H, const void *toRemove){
	unsigned int value;
	assert(H && toRemove);

	value = hash((char *)toRemove, H->length);
	removeElem_List(H->lists[value], toRemove);
}

void clear_Hash(Hash H){
	unsigned int i;
	assert(H);

	for (i = 0; i < H->length; ++i)
		clear_List(H->lists[i]);
}

void delete_Hash(Hash H){
	unsigned int i;
	assert(H);

	for (i = 0; i < H->length; ++i)
		delete_List(H->lists[i]);

	free(H->lists);
	free(H);
}

int find_Hash(Hash H, const void *toFind){
	unsigned int value;
	assert(H);

	value = hash((char *)toFind, H->length);

	if (find_List(H->lists[value], toFind))
		return 1;
	return 0;
}

void printBucket_Hash(Hash H, unsigned int index, FILE * stream){
	assert(H && stream);

	print_List(H->lists[index], stream);
}

void print_Hash(Hash H, FILE * stream){
	unsigned int i;
	
	for (i = 0; i < H->length; ++i)
		if (begin_List(H->lists[i]))
			printBucket_Hash(H, i, stream);
}

Hash resize_Hash(Hash H, unsigned int newLength){
	List l;
	List_Iter it;
	unsigned int i;
	Hash newHash;

	assert(newLength);

	newHash = new_Hash(newLength);

	for (i = 0; i < H->length; ++i){
		l = H->lists[i];
		it = begin_List(l);
		while (it != end_List(l)){
			add_Hash(newHash, getElem_List(l, it));

			it = next_List(l, it);
		}
	}

	delete_Hash(H);

	return newHash;
}

void resizeDouble_Hash(Hash *H){
	assert(*H);

	*H = resize_Hash(*H, (*H)->length * 2);
}

void resizeHalve_Hash(Hash *H){
	assert(*H);

	*H = resize_Hash(*H, (*H)->length / 2);
}

/**
 * Functie de hash bazata pe djb2 a lui Dan Bernstein
 * http://www.cse.yorku.ca/~oz/hash.html
 * @return valoarea de dispersie (cheia)
 */

unsigned int hash(const char *str, unsigned int hash_length)
{
	unsigned int hash = 5381;
	int c;

	while ( (c = *str++) != 0 )
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return (hash % hash_length);
}
