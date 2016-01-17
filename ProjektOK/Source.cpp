#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>

#include "ACO.h"

using namespace std;

// Super projekt na OK (´◉◞౪◟◉)

int main(){
	srand((unsigned int)time(NULL));
	int n = 50;
	ACO *aco;
	aco = new ACO(Parameters::Tasks::NUMBER, Parameters::Ants::NUMBER);

	aco->generateTasks(Parameters::Tasks::Length::MAX, Parameters::Tasks::Length::MIN);
	aco->generateBreaks();
	
	Solution solution = aco->generateRandomSolution();
	aco->printSolution(solution);
	std::cout << aco->getSolutionLength(solution) << std::endl;

	aco->feromoneEvaporation(Parameters::Feromone_Table::VAPORING);
	aco->smoothingFeromoneTable();

	aco->loadFromFile("Instance one");

	delete aco;

	system("pause");
	return 0;
}