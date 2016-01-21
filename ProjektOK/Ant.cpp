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

Solution Ants::generateSingleSolution(int turn)
{
	Solution retVal;
	std::vector<bool> unasignedTasks;

	for (int i = 0; i < number_of_tasks; i++) {
		unasignedTasks.push_back(true);
	}
	
	retVal.resize(2);
	for (auto &row : retVal)
		row.resize(number_of_tasks);
	int randomVal = rand() % number_of_tasks; 
	retVal[0][0] = randomVal;
	unasignedTasks[randomVal] = false;

	for (int i = 1; i < number_of_tasks; i++) {
		int nextElement = pickNextElenemtForSolution(isItUsingTable(turn), retVal[0][i-1], unasignedTasks);
		for (auto &value : retVal) {
			value[i] = nextElement;
		}
		unasignedTasks[retVal[0][i]] = false;
	}
	return retVal;
}

void Ants::generateSolutionTable(std::vector<Solution> * solutionTable, int turn)
{
	for (int i = 0; i < number_of_ants; i++) {
		solutionTable->push_back(generateSingleSolution(turn));
	}
}

void Ants::writeSolutionTableToFeromoneTable(std::vector<Solution> solutionTable)
{
	for (auto solution : solutionTable) {
		writeFeromoneToTable(solution);
	}
}

int Ants::pickNextElenemtForSolution(bool useTable, int previousTask, std::vector<bool> &unasignedTasks)
{
	int retVal;

	if (!useTable) {
		int ball = rand() % number_of_tasks;
		int i = -1;
		while (!unasignedTasks[++i]);
		while (ball > 0) {
			i++;
			if (i >= number_of_tasks)
				i = 0;

			if (unasignedTasks[i]) {
				ball--;
			}
		}
		retVal = i;
	}
	else {
		int sumOfAll = 0;
		int i = -1;
		for (auto feromone : (*feromone_table)[previousTask]) {
			if (unasignedTasks[++i])
				sumOfAll += feromone;
		}
		if (sumOfAll == 0)
			sumOfAll = 1;

		int ball = rand() % sumOfAll;
		
		i = 0;
		while (ball > 0) {
			i++;
			if (i >= number_of_tasks)
				i = 0;
			if (unasignedTasks[i])
				ball -= (*feromone_table)[previousTask][i];
		}
		retVal = i;
	}
	return retVal;
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

Solution Ants::generateFinalSolution(int turn)
{
	std::vector<Solution> solutionTable;

	generateSolutionTable(&solutionTable, turn);

	writeSolutionTableToFeromoneTable(solutionTable);

	return shortestSolution(solutionTable);
}

void Ants::jumpToReadyTime(int task, int * pointer, int * currentBreak)
{
	if ((*pointer) > (*tasks)[task][2])
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
	}
	else {
		(*pointer) = (*tasks)[task][2];
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
	for (int i = (*secondMachinePointer); (*secondMachinePointer) < (*tasks)[task][1] + i; (*secondMachinePointer)++);
}

void Ants::writeFeromoneToTable(Solution solution)
{
	auto previousOperation = solution[0][0];

	int solutionLength = getSolutionLength(solution);

	for (auto &operation : solution[0]) {
		if (operation != previousOperation) {
			(*feromone_table)[previousOperation][operation] += ((sumOfTasksAndBreaks - solutionLength) + ((sumOfTasksAndBreaks - solutionLength)*Parameters::Feromone_Table::ADDING_BONUS))*Parameters::Feromone_Table::ADDING_DIVIDER;
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

	sumOfTasksAndBreaks = 0;

	for (auto element : (*tasks)) {
		sumOfTasksAndBreaks += element[0] + element[1];
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