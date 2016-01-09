#pragma once
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <vector>
#include <iostream>

#include "Ant.h"

typedef std::vector<std::vector<float>> FeromoneTable;
typedef std::vector<std::vector<int>> Solution, Tasks, Breaks;

class ACO
{
	friend class Ant;

private:
	FeromoneTable feromone_table; //tablica dla 1 maszyny
	Tasks tasks; //tablica [n][2] z wylosowanymi czasami zadan dla maszyn
	Breaks breaks; //tablica [m][2] z czasami przerwan 0-rozpoczecie przerwy 1 maszyny, 1-zakonczenie
	int number_of_tasks, number_of_breaks, max_task_length, min_task_length;
	int number_of_ants;
	
	Solution solution; //tablica [2][n] z kolejnoœci¹ zadañ

	Ant *ants;

public:
	ACO();
	ACO(int number_of_tasks, int number_of_ants);
	~ACO();

	void generateTasks(int max, int min);
	void generateBreaks();
    Solution generateRandomSolution();

	std::vector<std::vector<int>> getSolution();
	void printSolution(Solution solution);

	int getSolutionLength(Solution solution);
};

