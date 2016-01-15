#include "Ant.h"



bool Ants::isItUsingTable(int turn)
{
	int i = turn; //tutaj wstawic rownanie na prawdopodobienstwo w %

	if ((rand() % 99) + 1 < i)
		return true;
	else
		return false;
}

void Ants::addNextElenemtToSolution(bool useTable, Solution tmp, std::vector<bool> alreadyUsed)
{
	std::vector<int> nextPossible;
	int last = (tmp.back())[0];
	int i = 0;
	int mod = 0;
	for (auto it : feromone_table[last][0]) {
		if (alreadyUsed[i] == false && it != (float)0) {
			nextPossible.push_back(i);
			mod += it * 10;
		}
		i++;
	}

	int choosenOne = rand() % mod;
	
}

void Ants::writeFeromoneToTable(Solution solution)
{
	auto prev = solution[0][0];

	float solutionLength = getSolutionLength(solution);

	std::cout << "Solution Length: " << solutionLength << "\n";


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
	std::cout << "First task 1st machine: " << solution[0][0] << std::endl;
	std::cout << "First task 2nd machine: " << solution[1][0] << std::endl;

	int currentBreak = 0;
	int pointer = 0;
	int secondMachinePointer = 0;
	for (auto task : solution[0]) {
		if (currentBreak < number_of_breaks) {
			if ((*tasks)[task][0] >
				((*breaks)[currentBreak][0] - pointer)) {
				while (pointer < (*breaks)[currentBreak][0]) {
					pointer++;
				}
				while (pointer < (*breaks)[currentBreak][1]) {
					pointer++;
				}
				currentBreak++;
			}
		}
		for (int i = pointer; pointer < (*tasks)[task][0] + i; pointer++);
		if (task == 0)
			secondMachinePointer = pointer;
		for (int i = secondMachinePointer; secondMachinePointer < (*tasks)[task][1] + i; secondMachinePointer++);
	}
	return secondMachinePointer;
}