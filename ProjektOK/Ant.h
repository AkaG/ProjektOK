#pragma once
#include <cstdlib>
#include <cstdio>
#include <ctime>

class Instance
{
private:
	std::vector<std::vector<float>> feromone_table; //tablica dla 1 maszyny
	std::vector<std::vector<int>> tasks; //tablica [n][2] z wylosowanymi czasami zadan dla maszyn
	std::vector<std::vector<int>> breaks; //tablica [m][4] z czasami przerwan 0-rozpoczecie przerwy 1 maszyny, 1-zakonczenie, 2-rozpoczecie dla 2 maszymy, 3-zakonczenie
				  //czy robimy wspolne przerwy dla maszyn?
	int number_of_tasks, number_of_breaks, max_task_length, min_task_length; 
	
	std::vector<std::vector<int>> solution; //tablica [2][n] czasów rozpoczêcia poszczególnych zadañ na obu maszynach
public:
	Instance();
	Instance(int n);
	~Instance();

	void generate(int max, int min);
	void generateBreaks();
	void generateRandomSolution();

	std::vector<std::vector<int>> getSolution();
};

