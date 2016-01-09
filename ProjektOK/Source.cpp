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
	Instance *instance;
	instance = new Instance(50);

	instance->generateTasks(100, 25);
	instance->generateBreaks();
	instance->printSolution(instance->generateRandomSolution());

	delete instance;
	system("pause");
	return 0;
}