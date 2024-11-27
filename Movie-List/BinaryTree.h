#ifndef _BINARYTREE_H
#define _BINARYTREE_H

#include "NodeTypes.h"

BTNode * createBTNode (Movie data);
void preOrder (BTNode * root);
void inOrder (BTNode * root);
void postOrder (BTNode * root);

int moment (BTNode * root);
bool contains (BTNode * root, int key);
Movie maximum (BTNode * root);
int numOneChild (BTNode * root);
int numTerminal (BTNode * root);

int nodeDepth (BTNode * node);

int height (BTNode * root);
void levelOrder (BTNode * root);
void clearBT (BTNode * root);

#endif
