#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>

#include "Ant.h"

using namespace std;

// Super projekt na OK (´◉◞౪◟◉)

int main(){
	int n = 50;
	Instance *instance;
	instance = new Instance(50);

	instance->generate(10000, 10);
	instance->generateBreaks();

	delete instance;
	return 0;
}