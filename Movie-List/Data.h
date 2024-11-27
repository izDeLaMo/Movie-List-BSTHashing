#ifndef _DATA_H
#define _DATA_H

#include <iostream>
	using namespace std;

#define MAX_ELEMENTS 1000
#define EMPTY		 ""

struct Movie {
	string ID;
	int yearReleased;
	int duration;
	string genre;
	string title;
};

#endif
