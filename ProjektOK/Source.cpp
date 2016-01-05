#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>

#include "Ant.h"

using namespace std;

// Super projekt na OK (´◉◞౪◟◉)

int main(){
	int n = 50;
	Ant *ant;
	ant = new Ant(50);

	ant->generateInst(10000, 10);
	ant->generateBreaks();

	delete ant;
	return 0;
}