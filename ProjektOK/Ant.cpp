#include "Ant.h"



void Ants::writeFeromoneToTable(Solution solution)
{
	auto prev = solution[0][0];

	float solutionLength = getSolutionLength(solution);

	std::cout << "\nSolution Length: " << solutionLength << "\n";

	for (auto &i : solution[0]) {
		if (i != prev) {

			(*feromone_table)[prev][i] += 1.f/solutionLength;

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

Ants::Ants(int n, FeromoneTable *table, Tasks tasks, Breaks breaks, int number_of_tasks, int number_of_breaks)
{
	number_of_ants = n;
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
		if (currentBreak < number_of_breaks) {
			if (tasks[task][0] >
				(breaks[currentBreak][0] - pointer)) {
				while (pointer < breaks[currentBreak][0]) {
					pointer++;
				}
				while (pointer < breaks[currentBreak][1]) {
					pointer++;
				}
				currentBreak++;
			}
		}
		for (int i = pointer; pointer < tasks[task][0] + i; pointer++);
		if (task == 0)
			secondMachinePointer = pointer;
		for (int i = secondMachinePointer; secondMachinePointer < tasks[task][1] + i; secondMachinePointer++);
	}
	return secondMachinePointer;
}