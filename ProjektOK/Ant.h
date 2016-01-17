#pragma once

#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <vector>
#include <iostream>

#include "Parameters.h"

typedef std::vector<std::vector<int>> FeromoneTable;
typedef std::vector<std::vector<int>> Solution, Tasks, Breaks;

class Ants
{
private:
	FeromoneTable *feromone_table;
	Tasks *tasks;
	Breaks *breaks;
	int sumOfTasksAndBreaks;
	int number_of_tasks, number_of_breaks;
	int number_of_ants;

	bool isItUsingTable(int turn);
	void pickNextElenemtForSolution(bool useTable, Solution &tmp, std::vector<int> unasignedTasks);
	Solution shortestSolution(std::vector<Solution> solutionTable);
	Solution generateFinalSolution();

	void jumpToReadyTime(int task, int *pointer, int *currentBreak);
	void findPlaceInBreaks(int task, int *pointer, int *currentBreak);
	void putInFirstMachine(int task, int *pointer);
	void putInSecondMachine(int task, int *pointer, int *secondMachinePointer);
public:
	void writeFeromoneToTable(Solution solution);
	int getSolutionLength(Solution solution);

public:
	Ants();
	Ants(FeromoneTable *feromoneTable, Tasks *tasks, Breaks *breaks, int number_of_tasks, int number_of_breaks, int number_of_ants);
	~Ants();
};

