#include "Ant.h"


Ant::Ant()
{
}


Ant::Ant(int n)
{
	this->n = n;
	this->m = (rand() % (n / 2 - 2)) + 2;

	tab1 = new int *[n];
	for (int i = 0; i < n; i++){
		tab1[i] = new int[n];
	}

	tab2 = new int *[n];
	for (int i = 0; i < n; i++){
		tab2[i] = new int[n];
	}

	inst = new int *[n];
	for (int i = 0; i < n; i++){
		inst[i] = new int[2];
	}

	breaks = new int *[this->m];
	for (int i = 0; i < this->m; i++){
		breaks[i] = new int[4];
	}
}

Ant::~Ant()
{
	for (int i = 0; i < n; i++){
		delete[] tab1[i];
	}
	delete[] tab1;
	tab1 = NULL;

	for (int i = 0; i < n; i++){
		delete[] tab2[i];
	}
	delete[] tab2;
	tab2 = NULL;

	for (int i = 0; i < n; i++){
		delete[] inst[i];
	}
	delete[] inst;
	inst = NULL;

	for (int i = 0; i < m; i++){
		delete[] breaks[i];
	}
	delete[] breaks;
	breaks = NULL;
}


void Ant::generateInst(int max, int min)
{
	this->maxDl = max;
	this->minDl = min;

	for (int i = 0; i < n; i++){
		inst[i][0] = (rand() % (maxDl - minDl)) + minDl;
		inst[i][1] = (rand() % (maxDl - minDl)) + minDl;
	}
}

void Ant::generateBreaks()
{
	int sumaZadan = 0;
	int najkrotsze = maxDl;

	int minBreak = 5;
	int maxBreak = 50;

	for (int i = 0; i < n; i++){
		sumaZadan += inst[i][0];
		if (inst[i][0] < najkrotsze)
			najkrotsze = inst[i][0];
	}
	
	breaks[0][0] = ((rand() % 3) + 1) * najkrotsze;
	breaks[0][1] = breaks[0][0] + ((rand() % maxBreak) + minBreak);

	for (int i = 1; i < m; i++){
		breaks[i][0] = breaks[i - i][1] + ((rand() % (3 * maxDl)) + minDl);
		breaks[i][1] = breaks[i][0] + ((rand() % maxBreak) + minBreak);
	}
}