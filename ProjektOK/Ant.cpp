#include "Ant.h"



bool Ants::isItUsingTable(int turn)
{
	int i = turn; //tutaj wstawic rownanie na prawdopodobienstwo w %

	if ((rand() % 99) + 1 < i)
		return true;
	else
		return false;
}

void Ants::addNextElenemtToSolution(bool useTable, Solution &tmp, std::vector<bool> alreadyUsed)
{
	std::vector<int> nextPossible;
	int last = (tmp.back())[0];
	int i = 0;
	int mod = 0;
	for (auto it : (*feromone_table)[last]) {
		if (alreadyUsed[i] == false && it != (float)0) {
			nextPossible.push_back(i);
			mod += it;
		}
		i++;
	}

	int choosenOne = rand() % mod;

	float sum = 0;

	for (auto it : nextPossible) {
		if (choosenOne >= sum && choosenOne < sum + (*feromone_table)[last][it]) {
			alreadyUsed[it] = true;
			std::vector<int> vect;
			vect.push_back(it);
			vect.push_back(it);
			tmp.push_back(vect);
			return;
		}
		sum += (*feromone_table)[last][it];
	}
	
}

void Ants::generateFinalSolution()
{

}

void Ants::jumpToReadyTime(int task, int * pointer, int * currentBreak)
{
	if ((*pointer) < (*tasks)[task][2])
		return;
	else if (*currentBreak < number_of_breaks) {
		while (((*currentBreak) < (number_of_breaks - 1)) &&
			((*tasks)[task][2] > (*breaks)[(*currentBreak)][1])) {
			(*currentBreak)++;
		}
		if ((*tasks)[task][2] < (*breaks)[(*currentBreak)][0])
			(*pointer) = (*tasks)[task][2];
		else if ((*tasks)[task][2] < (*breaks)[(*currentBreak)][1])
			(*pointer) = (*tasks)[task][2];
		else {
			(*pointer) = (*tasks)[task][2];
			(*currentBreak)++;
		}
	} else {
		*pointer = (*tasks)[task][2];
	}
}

void Ants::findPlaceInBreaks(int task, int * pointer, int * currentBreak)
{
	if (*currentBreak < number_of_breaks) {
		while (((*currentBreak) < number_of_breaks) &&
			((*tasks)[task][0] >
			((*breaks)[*currentBreak][0] - (*pointer)))) {

			(*pointer) = (*breaks)[(*currentBreak)][1];
			(*currentBreak)++;
		}
	}
	else {
		return;
	}
}

void Ants::putInFirstMachine(int task, int * pointer)
{
	for (int i = *pointer; *pointer < (*tasks)[task][0] + i; (*pointer)++);
}

void Ants::putInSecondMachine(int task, int * pointer, int *secondMachinePointer)
{
	if (task == 0)
		(*secondMachinePointer) = (*pointer);
	for (int i = (*secondMachinePointer); (*secondMachinePointer) < (*tasks)[task][1] + i; ((*secondMachinePointer))++); 
}

void Ants::writeFeromoneToTable(Solution solution)
{
	auto prev = solution[0][0];

	float solutionLength = getSolutionLength(solution);

	std::cout << "Solution Length: " << solutionLength << "\n";


	for (auto &i : solution[0]) {
		if (i != prev) {
			(*feromone_table)[prev][i] += 1.f / solutionLength;
			prev = i;
		}
	}
	for (auto i : (*feromone_table)) {
		for (auto j : i) {
			//std::cout << j << "\t|\t";
		}
		//std::cout << std::endl;
	}
	//std::cout << std::endl;
}

Ants::Ants()
{
}

Ants::Ants(FeromoneTable *table, Tasks *tasks, Breaks *breaks, int number_of_tasks, int number_of_breaks)
{
	feromone_table = table;
	this->tasks = tasks;
	this->breaks = breaks;
	this->number_of_breaks = number_of_breaks;
	this->number_of_tasks = number_of_tasks;
}

Ants::~Ants()
{
}

int Ants::getSolutionLength(Solution solution)
{
	int currentBreak = 0;
	int pointer = 0;
	int secondMachinePointer = 0;
	for (auto task : solution[0]) {
		jumpToReadyTime(task, &pointer, &currentBreak);

		findPlaceInBreaks(task, &pointer, &currentBreak);

		putInFirstMachine(task, &pointer);

		putInSecondMachine(task, &pointer, &secondMachinePointer);
	}
	return secondMachinePointer;
}