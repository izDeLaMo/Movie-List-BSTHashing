#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include "HashTable.h"
#include "BinaryTree.h"
#include "BinarySearchTree.h"
#include "Data.h"
using namespace std;

#define QUIT 99


int main () {
    char fileName[25] = "Movies.txt";
    char commandsFile[25] = "Commands.txt";
    ifstream infile;

    infile.open(commandsFile);
	
	if (!infile.is_open()) {
		cout << "Input file " << commandsFile << " could not be opened. Aborting ..." << endl;
	}
	
    int command;
    cout << "Initializing hash table from file..." << endl;
    HashTable *ht = initHashTableFromFile(23, fileName);

    if (ht != NULL) 
        cout << "Hash table initialized successfully." << endl;
    else 
       cout << "Failed to initialize hash table." << endl;
    
    cout << endl;
    
    cout << "Initializing binary search tree from file..." << endl;
    BTNode * root = initBSTFromFile (fileName);
    if (root != NULL) 
        cout << "Binary search tree initialized successfully." << endl;
    else 
        cout << "Failed to initialize binary search tree." << endl;
    
    cout << endl;
	infile>> command;
	while(command != 99){
		if(command == 10){
			cout << "COMMAND 10" << endl << endl;
			Movie newMovie;
			infile >> newMovie.ID >> newMovie.yearReleased >> newMovie.duration >> newMovie.genre >> ws;
			getline (infile, newMovie.title);
			displayMovie(newMovie);
			if(containsHT(ht, newMovie.ID) == -1 && containsBST(root, newMovie.ID) == NULL){
				insertHT (ht, newMovie);
				insertBST (root, newMovie);
				cout << "Movie inserted in the hash table and the BST" << endl;
			}
			else
				cout << "The movie is already in the hash table" << endl;
			cout << "----------------------------------------------------------------" << endl;
		}
		if(command ==11){
			cout << "COMMAND 11" << endl << endl;
			Movie newMovie;
			infile >> newMovie.ID;
			if(containsHT(ht, newMovie.ID) != -1){
				cout << "Movie "<< newMovie.ID <<" in the hash table" << endl;
				displayMovieHT (ht, newMovie.ID);
				cout <<"Length of the chain is " << lengthChain (ht, containsHT(ht, newMovie.ID))<< endl;
			}
			else
				cout << "Movie "<< newMovie.ID << " is not in the hash table" << endl;
			cout << endl;
			if(containsBST(root, newMovie.ID) != NULL){
				BTNode * keyNode = containsBST (root, newMovie.ID);
				cout << "Movie "<< newMovie.ID <<" in the BST" << endl;
				displayMovie(keyNode->data);
			}
			else
				cout << "Movie "<< newMovie.ID << " is not in the BST" << endl;
			cout << "----------------------------------------------------------------" << endl;
		}
		if(command ==13){
			cout << "COMMAND 13" << endl << endl;
			statisticsHT (ht);
			cout << endl;
			statisticsBST (root);
			cout << "----------------------------------------------------------------" << endl;
		}
		if(command == 20){
			cout << "COMMAND 20" << endl << endl;
			BTNode * curr = minimumBST (root);
			while(curr != NULL){
				cout<< curr->data.ID << " " ;
				curr = inOrderSuccessor(curr);
			}
			cout << endl << "----------------------------------------------------------------" << endl;
		}
		if(command == 21){
			cout << "COMMAND 21" << endl << endl;
			levelOrder (root);
			cout << "----------------------------------------------------------------" << endl;
		}
		if(command == 22){
			cout << "COMMAND 22" << endl << endl;
			string newMovie1;
			string newMovie2;
			infile >> newMovie1 >> newMovie2;
			cout << "Displaying all keys in the BST between " << newMovie1 <<" and "<< newMovie2 << endl;
			rangeBST (root, newMovie1, newMovie2);
			cout << "----------------------------------------------------------------" << endl;
		}
		if(command == 23){
			cout << "COMMAND 23" << endl << endl;
			char filename1[25];
			infile >> filename1;
			BTNode * root1 = initBSTFromFile (filename1);
    		if (root1 != NULL) 
        		cout << "Binary search tree initialized successfully." << endl;
    		 else 
        		cout << "Failed to initialize binary search tree." << endl;
    		cout <<"Root of BST created with " << root1->data.ID <<endl;
    		levelOrder (root1);
			if(isIsomorphic (root, root1))
				cout << "BSTs are Isomorphic" << endl;
			else
				cout << "BSTs are not Isomorphic" << endl;
			BTNode * nodey = minimumBST(root1);
			while(nodey != NULL){
				root1 = deleteBST(root1, nodey->data.ID);
				nodey = inOrderSuccessor (nodey);
			}
			cout << "----------------------------------------------------------------" << endl;
		}
		if(command == 12){
			cout << "COMMAND 12" << endl << endl;
			string deleteid;
			infile >> deleteid;
			BTNode * node2 = root;
			if(containsBST (root, deleteid) != NULL)
				cout << "Movie " << deleteid << " was deleted from BST" << endl;
			root = deleteBST(root, deleteid);
    		
			
			deleteHT (ht, deleteid);                
			cout << "----------------------------------------------------------------" << endl;
		}
	infile>> command;
	}
	cout << "Terminate the program." << endl;	
    return 0;
}
