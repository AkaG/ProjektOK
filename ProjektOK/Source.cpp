#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>

#include "ACO.h"

using namespace std;

// Super projekt na OK (´◉◞౪◟◉)

int main(){
	srand((unsigned int)time(NULL));
	ACO *aco;
	//aco = new ACO(Parameters::Tasks::NUMBER, Parameters::Ants::NUMBER);
	//aco->startAlgorithm();
	for (int i = 0;i < 1;i++) {
		aco = new ACO(std::to_string(1), Parameters::Ants::NUMBER);
		aco->startAlgorithm();
		aco->saveToFile(std::to_string(1).append("solved"));
		delete aco;
	}
	system("pause");
	return 0;
}