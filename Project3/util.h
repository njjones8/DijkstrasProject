#ifndef _util_h
#define _util_h 1
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include "graph.h"
int nextCommand(int*, int*, int*, int*);
Graph* initializeGraph();
int checkInput();
void clearInput();
void printQuery(std::string cmd, int c, int s, int d, int f);
#endif