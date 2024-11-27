#include <iostream>
#include <cstdlib>
#include <fstream>

#include "NodeTypes.h"
#include "BinaryTree.h"
#include "BinarySearchTree.h"
#include "Data.h"
using namespace std;

BTNode * initBSTFromFile (char fileName[]) {
	
	BTNode * root = NULL;
	
	ifstream inputFile;
	Movie movie;
	int numMovies;
	
	inputFile.open(fileName);
	
	if (!inputFile.is_open()) {
		cout << "Input file " << fileName << " could not be opened. Aborting ..." << endl;
		return root;
	}

	numMovies = 0;
	inputFile >> movie.ID;
		
	while (movie.ID != "END") {
		inputFile >> movie.yearReleased >> movie.duration >> movie.genre >> ws;
		getline (inputFile, movie.title);
		numMovies++;

		root = insertBST (root, movie);
		inputFile >> movie.ID;
	}

	inputFile.close();
	
	cout << numMovies << " movies read from " << fileName << " and stored in BST." << endl;
	
	return root;
}



BTNode * insertBST (BTNode * root, Movie data) {
	BTNode * newNode;
		
	if (root == NULL) {
		newNode = createBTNode (data);
		return newNode;
	}
	int rootnum = convertID2(root->data.ID);
	int datanum = convertID2(data.ID);
    if (datanum < rootnum) {
        root->left = insertBST(root->left, data);
        root->left->parent = root; 
    } else {
        root->right = insertBST(root->right, data);
        root->right->parent = root; 
    }
    
    return root;
}



BTNode * containsBST (BTNode * root, string key) {
	if(root == NULL)
		return NULL;
		
	int idnum = convertID2(key);
	int rootnum = convertID2(root->data.ID);
	
	if(rootnum == idnum)
		return root;
	if(idnum < rootnum)
		return containsBST(root->left, key);
	else
		return containsBST(root->right, key);
	}



BTNode * minimumBST (BTNode * root) {
	if(root == NULL)
		return NULL;
	if(root->left != NULL)
		return minimumBST(root->left);
	return root;
}

BTNode * maximumBST (BTNode * root) {
	if(root == NULL)
		return NULL;
	if(root->right != NULL)
		return maximumBST(root->right);
	return root;
}



BTNode * inOrderSuccessor (BTNode * node) {
	if(node == NULL)
		return NULL;
	if(node->right != NULL){
		BTNode * curr = node->right;
		while(curr->left != NULL){
			curr = curr->left;
		}
		return curr;
	}
	BTNode* parent = node->parent;
    while (parent != NULL && node == parent->right) {
        node = parent;
        parent = parent->parent;
    }

    return parent; 
}



void rangeBST (BTNode * root, string lowerID, string upperID) {
	if(root == NULL)
		return;
	int count = 0;
	int lowernum = convertID2(lowerID);
	int uppernum = convertID2(upperID);
	BTNode * min = minimumBST(root);
	BTNode * max = maximumBST(root);
	if(lowernum < convertID2(min->data.ID) || uppernum > convertID2(max->data.ID)){
		cout << "Range given is not within the BST" << endl;
		return;
	}
	BTNode * sNode = minimumBST (root);
	int snum = convertID2(sNode->data.ID);
	while(sNode != NULL && convertID2(sNode->data.ID) < lowernum){
		sNode = inOrderSuccessor (sNode);
	}
	while(sNode != NULL && convertID2(sNode->data.ID) <= uppernum){
		cout << sNode->data.ID << " " << endl;
		sNode = inOrderSuccessor (sNode);
		count++;
	}
	cout << count <<" keys in the range given" <<endl;
}
	


void statisticsBST (BTNode * root) {
	int h = height (root);
	int numT = numTerminal (root);
	BTNode * max = maximumBST (root);
	BTNode * min = minimumBST (root);
	cout << "Statistics on BST" << endl;
	cout << "The height of the binary tree : " << h <<endl;
	cout << "The number of non-terminal nodes : " << numT << endl; // this code was given but the output is different from sample output
	cout <<"The minimum key : " << min->data.ID <<endl;
	cout << "The maximum key : " << max->data.ID << endl;
}



bool isIsomorphic (BTNode * root1, BTNode * root2) {
	if(root1 == NULL && root2 == NULL)
		return true;
	if(root1 == NULL || root2 == NULL)
		return false;
	BTNode * curr1 = minimumBST(root1);
	BTNode * curr2 = minimumBST(root2);
	while (curr1 != NULL && curr2 != NULL){
		if(curr1->data.ID != curr2->data.ID)
			return false;
		curr1 = inOrderSuccessor (curr1);
		curr2 = inOrderSuccessor (curr2);
	}
	if(curr1 == NULL && curr2 == NULL)
		return true;
	return false;
}



BTNode* deleteBST(BTNode* root, string key) {
    if (root == NULL)
        return NULL;

    BTNode* node = containsBST(root, key);
    if (node == NULL) {
        cout << "Key is not in the BST" << endl;
        return root;
    }

    if (node->left == NULL && node->right == NULL) {
        if (node == root) {
            delete node; 
            return NULL;
        }
        BTNode* parent = node->parent;
        if (parent->left == node)
            parent->left = NULL;
        else
            parent->right = NULL;
        delete node; 
        return root;
    }

    if (node->left == NULL || node->right == NULL) {
        BTNode* child = (node->left != NULL) ? node->left : node->right;
        if (node == root) {
            child->parent = NULL;
            delete node; 
            return child;
        }
        BTNode* parent = node->parent;
        if (parent->left == node)
            parent->left = child;
        else
            parent->right = child;
        child->parent = parent;
        delete node;
        return root;
    }

    BTNode* succ = minimumBST(node->right); 
    node->data = succ->data; 

    if (succ->parent->left == succ)
        succ->parent->left = succ->right;
    else
        succ->parent->right = succ->right;
    if (succ->right != NULL)
        succ->right->parent = succ->parent;
    delete succ;
    return root;
}

int  convertID2(string id){
    if (id.substr(0, 2) == "tt") {
        return stoi(id.substr(2));
    } else {

        cout << "Error Invalid ID format" << endl;
        return -1;
    }
}

