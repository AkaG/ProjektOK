#pragma once

#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <vector>
#include <iostream>

typedef std::vector<std::vector<float>> FeromoneTable;
typedef std::vector<std::vector<int>> Solution, Tasks, Breaks;

class Ant
{
private:
	int number_of_ants;
	Solution solution;

public:
	Ant();
	Ant(int n);
	~Ant();
};

