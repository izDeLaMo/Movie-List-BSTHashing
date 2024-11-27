#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstring>
#include <conio.h>
#include "Data.h"
#include "HashTable.h"
   using namespace std;


HashTable * initHashTable (int sizeTable) {
    if (sizeTable > MAX_ELEMENTS) {
        cout << "SizeTable too large" << endl;
        return NULL;
    }
    HashTable *ht = new HashTable;
    ht->sizeTable = sizeTable;
    for (int i = 0; i < sizeTable; i++) {
        ht->elements[i] = NULL;
    }
    return ht;
}



HashTable * initHashTableFromFile (int sizeTable, char fileName[]) {

	ifstream inputFile;
	ofstream outputFile;

	Movie movie;
	int numMovies;
	
	HashTable * ht = initHashTable(sizeTable);	
	
	inputFile.open(fileName);
	
	if (!inputFile.is_open()) {
		cout << "Input file " << fileName << " could not be opened. Aborting ..." << endl;
		return ht;
	}
	
	numMovies = 0;
	inputFile >> movie.ID;
	
	while (movie.ID != "END") {
		inputFile >> movie.yearReleased >> movie.duration >> movie.genre >> ws;
		getline (inputFile, movie.title);
		numMovies++;

		insertHT (ht, movie);
		inputFile >> movie.ID;
	}

	inputFile.close();
	
	cout << numMovies << " movies read from " << fileName << " and stored in hash table." << endl;
	
	return ht;
}



int containsHT(HashTable *ht, string key) {
    if (ht == NULL || ht->elements == NULL) 
		return -1; 
    int loc = findLoc(ht, key);
    if (loc < 0 || loc >= ht->sizeTable) 
		return -1; 

    LLNode *curr = ht->elements[loc];
    while (curr != NULL) {
        if (curr->data.ID == key)
            return loc;
        curr = curr->next;
    }
    return -1;
}



void displayMovie (Movie movie) {
	
	cout << "ID:              " << movie.ID << endl;
	cout << "TITLE:           " << movie.title << endl;
	cout << "YEAR RELEASED:   " << movie.yearReleased << endl;
	cout << "DURATION:        " << movie.duration << endl;
	cout << "GENRE:           " << movie.genre << endl;
	cout << endl;	
}



void displayMovieHT (HashTable * ht, string key) {
	int loc = findLoc(ht, key);
	LLNode * curr = ht->elements[loc];
	while(curr != NULL){
		if(curr->data.ID == key){
			displayMovie(curr->data);
			return;
		}
		else
			curr = curr->next;
	}
	cout << "Movie was not found " << endl;
}


	
int lengthChain (HashTable * ht, int location) {
	int count = 0;
	LLNode * curr = ht->elements[location];
	while(curr != NULL){
		count++;
		curr = curr->next;
	}
	return count;
}



LLNode * createNode (Movie movie) {
	LLNode * newNode;
	
	newNode = new LLNode;
	
	newNode->data = movie;
	newNode->next = NULL;
	
	return newNode;
}



void insertHT (HashTable * ht, Movie movie) {
	LLNode * newNode = createNode(movie);
	int loc = findLoc(ht, movie.ID);
	LLNode * current = ht->elements[loc];
    while (current != NULL) {
        if (current->data.ID == movie.ID) {
            return;
        }
        current = current->next;
    }
    newNode->next = ht->elements[loc];
    ht->elements[loc] = newNode;
}

void statisticsHT (HashTable * ht) {
	int filled = 0;
	int empty = 0;
	int longest = 0;
	int chain = 0;
 	for(int x = 0; x < ht->sizeTable; x++){
		if(ht->elements[x] == NULL)
			empty++;
		else{
			filled++;
			chain = lengthChain (ht, x);
			if(chain > longest)
				longest = chain;
		}
	}
	cout << "Statistics on hash table" << endl;
	cout << "The number of location in the hash table that are filled: " << filled << endl;
	cout << "The number of location in the hash table that are empty: " << empty << endl;
	cout << "The Length of the longest chain in the hash table: " << longest << endl;
}




void deleteHT (HashTable * ht, string key) {
	int loc = findLoc(ht, key);
	if(loc == -1 || ht->elements[loc] == NULL){
		cout << "Key is not in the hash talbe" << endl;
		return;
	}
	LLNode * curr = ht->elements[loc];
	if (curr->data.ID == key){
		ht->elements[loc] = curr->next;
		cout << "Movie "<< key << " was deleted from hash table" << endl;
		delete curr;
	}
	LLNode * prev = curr;
	curr = curr->next;
	while (curr != NULL){
		if (curr->data.ID == key){
			prev->next = curr->next;
			cout << "Movie "<< key << " was deleted from hash table" << endl;
			delete curr;
		}
		else{
			curr = curr->next;
			prev = prev->next;
		}
	}
}


int findLoc(HashTable * ht, string key){
	int idNum = convertID(key);
	if (idNum == -1) {
        return -1;
    }
	int loc = idNum % ht->sizeTable;
	return loc;
}	
int convertID(string id) {

    if (id.substr(0, 2) == "tt") {

        return stoi(id.substr(2));
    } else {

        cout << "Error Invalid ID format" << endl;
        return -1;
    }
}
