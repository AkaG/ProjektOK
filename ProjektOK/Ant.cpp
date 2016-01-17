#include "Ant.h"



bool Ants::isItUsingTable(int turn)
{
	float c = (float)Parameters::Ants::TABLE_PROBABILITY;
	int i = c/((float)turn + c/100); //tutaj wstawic rownanie na prawdopodobienstwo w %

	if ((rand() % 99) + 1 < i)
		return false;
	else
		return true;
}

int Ants::pickNextElenemtForSolution(bool useTable, int previousTask, std::vector<int> unasignedTasks)
{
	int sumOfAll = 0;
	
	if (!useTable)
		;
}

Solution Ants::shortestSolution(std::vector<Solution> solutionTable)
{
	Solution retVal = solutionTable[0];

	int minTime = getSolutionLength(solutionTable[0]);
	for (auto solution : solutionTable) {
		int testedSolutionLength = getSolutionLength(solution);
		if (minTime > testedSolutionLength) {
			retVal = solution;
			minTime = testedSolutionLength;
		}
	}

	return retVal;
}

Solution Ants::generateFinalSolution()
{
	std::vector<Solution> solutionTable;
	
	generateSolutionTable(&solutionTable);

	wrtieSolutionTableToFeromoneTable(solutionTable);

	return shortestSolution(solutionTable);
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
	if ((*secondMachinePointer) < (*pointer))
		(*secondMachinePointer) = (*pointer);
	for (int i = (*secondMachinePointer); (*secondMachinePointer) < (*tasks)[task][1] + i; ((*secondMachinePointer))++); 
}

void Ants::writeFeromoneToTable(Solution solution)
{
	auto previousOperation = solution[0][0];

	int solutionLength = getSolutionLength(solution);

	std::cout << "Solution Length: " << solutionLength << "\n";

	for (auto &operation : solution[0]) {
		if (operation != previousOperation) {
			(*feromone_table)[previousOperation][operation] += sumOfTasksAndBreaks - solutionLength;
			previousOperation = operation;
		}
	}

}

Ants::Ants()
{
}

Ants::Ants(FeromoneTable *table, Tasks *tasks, Breaks *breaks, int number_of_tasks, int number_of_breaks, int number_of_ants)
{
	feromone_table = table;
	this->tasks = tasks;
	this->breaks = breaks;
	this->number_of_breaks = number_of_breaks;
	this->number_of_tasks = number_of_tasks;
	this->number_of_ants = number_of_ants;

	this->sumOfTasksAndBreaks = 0;
	for (auto element : (*tasks)[0]) {
		sumOfTasksAndBreaks += element;
	}
	sumOfTasksAndBreaks += (*breaks)[number_of_breaks - 1][1];
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