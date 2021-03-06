#pragma once
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Ant.h"

class ACO
{
	friend class Ants;

private:
	FeromoneTable feromone_table; //tablica dla 1 maszyny
	
	// tablica [n][3] z czasem gotowości wylosowanymi 
	// czasami zadan na poszczególne maszyny
	Tasks tasks; 
	Breaks breaks;	//tablica [m][2] z czasami przerwan 0-rozpoczecie przerwy 1 maszyny, 1-zakonczenie
	int number_of_tasks, number_of_breaks, max_task_length, min_task_length;
	int number_of_ants;
	
	Solution solution; //tablica [2][n] z kolejnością zadań
	Solution startingSolution;

	std::string instanceNumber;

	Ants *ants;

public:
	ACO();
	ACO(int number_of_tasks, int number_of_ants);
	ACO(std::string fileName, int number_of_ants);
	~ACO();

	void generateTasks(int max, int min);
	void generateBreaks();
    Solution generateRandomSolution();
	Solution getSolution();
	void printSolution(Solution solution);

	int getSolutionLength(Solution solution);

	void feromoneEvaporation(float p);

	void smoothingFeromoneTable();

	void startAlgorithm();
	
	void loadFromFile(std::string name);
	void saveToFile(std::string name);

};

