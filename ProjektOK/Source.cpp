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

	aco->startAlgorithm();

	delete aco;

	system("pause");
	return 0;
}