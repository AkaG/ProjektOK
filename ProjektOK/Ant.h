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
	Solution generateSingleSolution(int turn);
	int pickNextElenemtForSolution(bool useTable, int previousTask, std::vector<bool> &unasignedTasks);
	void generateSolutionTable(std::vector<Solution> *solutionTable, int turn);
	void writeSolutionTableToFeromoneTable(std::vector<Solution> solutionTable);
	Solution shortestSolution(std::vector<Solution> solutionTable);

public:
	void jumpToReadyTime(int task, int *pointer, int *currentBreak);
	void findPlaceInBreaks(int task, int *pointer, int *currentBreak);
	void putInFirstMachine(int task, int *pointer);
	void putInSecondMachine(int task, int *pointer, int *secondMachinePointer);

	void writeFeromoneToTable(Solution solution);
	int getSolutionLength(Solution solution);

public:
	Ants();
	Solution generateFinalSolution(int turn);
	Ants(FeromoneTable *feromoneTable, Tasks *tasks, Breaks *breaks, int number_of_tasks, int number_of_breaks, int number_of_ants);
	~Ants();
};

