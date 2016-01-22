#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>

#include "ACO.h"

using namespace std;

int main(){
	srand((unsigned int)time(NULL));
	ACO *aco;
	//aco = new ACO(Parameters::Tasks::NUMBER, Parameters::Ants::NUMBER);

	for (int i = 0;i < 10;i++) {
			aco = new ACO(std::to_string(i).append(".txt"), Parameters::Ants::NUMBER);
			aco->startAlgorithm();
			aco->saveToFile(std::to_string(i).append("solved.txt"));
			cout << endl;
			delete aco;
	}
	system("pause");
	return 0;
}