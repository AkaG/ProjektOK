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
	for (int i = 0;i < 5;i++) {
		aco = new ACO(std::to_string(i), Parameters::Ants::NUMBER);
		aco->startAlgorithm();
		aco->saveToFile(std::to_string(i).append("solved"));
		delete aco;
	}
	system("pause");
	return 0;
}