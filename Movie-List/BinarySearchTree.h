#ifndef _BINARYSEARCHTREE_H
#define _BINARYSEARCHTREE_H

#include "Data.h"
using namespace std;

BTNode * initBSTFromFile (char fileName[]);
BTNode * insertBST (BTNode * root, Movie data);
BTNode * insertBSTRec (BTNode * root, Movie data);
BTNode * containsBST (BTNode * root, string key);
BTNode * deleteBST (BTNode * root, string key);

BTNode * minimumBST (BTNode * root);
BTNode * maximumBST (BTNode * root);
BTNode * inOrderSuccessor (BTNode * btNode);
void rangeBST (BTNode * root, string lowerID, string upperID);

void statisticsBST (BTNode * root);

bool isIsomorphic (BTNode * root1, BTNode * root2);

int  convertID2(string id);
#endif
