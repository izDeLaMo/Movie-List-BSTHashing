#include <iostream>
#include <cstdlib>
#include "BinaryTree.h"
#include "Queue.h"
#include "Data.h"

using namespace std;



BTNode * createBTNode (Movie data) {
	BTNode * newNode; 
   
	newNode = new BTNode;
   
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->parent = NULL;
   
	return newNode;
}



void preOrder (BTNode * root) {
	
	if (root == NULL)
		return;
		
	cout << root->data.ID << " ";

	preOrder (root->left);
	preOrder (root->right);
}



void inOrder (BTNode * root) {
	
	if (root == NULL)
		return;

	inOrder (root->left);
	
	cout << root->data.ID << " ";
	
	inOrder (root->right);
}



void postOrder (BTNode * root) {
	
	if (root == NULL)
		return;

	postOrder (root->left);
	postOrder (root->right);
	
	cout << root->data.ID << " ";
}



int moment (BTNode * root) {

	if (root == NULL)
		return 0;
		
	return (1 + moment (root->left) + moment (root->right));
}



int numOneChild (BTNode * root) {

	if (root == NULL)
		return 0;
		
	if (root->left == NULL && root->right == NULL)
		return 0;

	if (root->left == NULL)
		return 1 + numOneChild (root->right);
	else
	if (root->right == NULL)
		return 1 + numOneChild (root->left);
	else
		return (numOneChild (root->left) + numOneChild (root->right));
}



int numTerminal (BTNode * root) {

	if (root == NULL)
		return 0;
		
	if (root->left == NULL && root->right == NULL)
		return 1;
		
	return (numTerminal (root->left) + numTerminal (root->right));
}



int nodeDepth (BTNode * node) {
	int branch;
	
	branch = 0;
	
	if (node == NULL)
		return -1;
		
	while (node->parent != NULL) {
		node = node->parent;
		branch++;
	}
	
	return branch;
}



int height (BTNode * root) {
	if(root == NULL)
		return 0;
	
	int leftNum = height(root->left);
	int rightNum = height (root->right);
	
	if (leftNum > rightNum)
		return leftNum + 1;
	else
		return rightNum +1;

}



void levelOrder(BTNode *root) {
    if (root == NULL) 
        return;

    Queue *q = initQueue(moment(root));
    enqueue(q, root);

    cout << "Level order traversal of BST:" << endl;

    int levelnum = 0;

    while (!isEmptyQueue(q)) {
        int levelsize = 0; 

        Queue *tempQueue = initQueue(moment(root));
        while (!isEmptyQueue(q)) {
            BTNode *node = dequeue(q);
            enqueue(tempQueue, node); 
            levelsize++;
        }

        while (!isEmptyQueue(tempQueue)) {
            enqueue(q, dequeue(tempQueue));
        }

        cout << levelsize << " nodes at Level " << levelnum << ": ";

        for (int i = 0; i < levelsize; ++i) {
            BTNode *node = dequeue(q);
            cout << node->data.ID;
            if (i < levelsize - 1) 
                cout << " ";

            if (node->left != NULL)
                enqueue(q, node->left);
            if (node->right != NULL)
                enqueue(q, node->right);
        }
        cout << endl; 
        levelnum++;
    }
}


void clearBT (BTNode * root) {
	Queue * q = initQueue (moment (root));
	enqueue (q, root);
	while(!isEmptyQueue (q)){
			BTNode * node = dequeue(q);
			if(node->left != NULL)
				enqueue(q,node->left);
			if(node->right != NULL)
				enqueue(q,node->right);	
			delete node;
	}                       
}

