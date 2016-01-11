#pragma once
#include <vector>
#include <fstream>

typedef std::vector<std::vector<int>> Tasks, Breaks;

class Instance {
private:
	int ID;
	Tasks tasks;
	Breaks breaks;
	int number_of_tasks, number_of_breaks, max_task_length, min_task_length;

public:
	Instance(int number_of_tasks, int ID);

	void generateTasks(int max, int min);
	void generateBreaks();

	void saveToFile(char* filename);
};