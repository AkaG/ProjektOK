#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>

#include "ACO.h"

using namespace std;

// Super projekt na OK (´◉◞౪◟◉)

int main(){
	srand(time(NULL));
	int n = 50;
	ACO *aco;
	aco = new ACO(50, 20);

	aco->generateTasks(100, 25);
	aco->generateBreaks();
	aco->printSolution(aco->generateRandomSolution());

	delete aco;

	system("pause");
	return 0;
}