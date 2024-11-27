#ifndef _HASHTABLE_H
#define _HASHTABLE_H

#include "Nodetypes.h"

struct HashTable {
	LLNode * elements [MAX_ELEMENTS];
	int sizeTable;
};
	
HashTable * initHashTable (int sizeTable);
HashTable * initHashTableFromFile (int sizeTable, char fileName[]);
void insertHT (HashTable * ht, Movie m);
int containsHT (HashTable * ht, string key);
void deleteHT (HashTable * ht, string key);
int lengthChain (HashTable * ht, int location);
void displayMovie (Movie movie);
void displayMovieHT (HashTable * ht, string key);
void statisticsHT (HashTable * ht);
int findLoc(HashTable * ht, string key);
int convertID(string id);
#endif
