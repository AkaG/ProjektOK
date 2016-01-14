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
	
	Solution solution = aco->generateRandomSolution();
	aco->printSolution(solution);
	std::cout << aco->getSolutionLength(solution) << std::endl;

	aco->feromoneEvaporation(5);
	aco->smoothingFeromoneTable();

	aco->loadFromFile("Instance one");

	delete aco;

	system("pause");
	return 0;
}