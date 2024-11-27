#ifndef _NODETYPES_H
#define _NODETYPES_H

#include <iostream>
#include "Data.h"
using namespace std;


struct LLNode {
	Movie data;
	LLNode * next;	
};


struct BTNode {
	Movie data;
	BTNode * left;
	BTNode * right;
	BTNode * parent;
};

#endif
