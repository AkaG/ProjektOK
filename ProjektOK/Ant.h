#pragma once
#include <cstdlib>
#include <cstdio>
#include <ctime>

class Ant
{
private:
	int **tab1; //tablica dla 1 maszyny
	int **tab2; //tablica dla 2 maszyny
	int **inst; //tablica [n][2] z wylosowanymi czasami zadan dla maszyn
	int **breaks; //tablica [m][4] z czasami przerwan 0-rozpoczecie przerwy 1 maszyny, 1-zakonczenie, 2-rozpoczecie dla 2 maszymy, 3-zakonczenie
				  //czy robimy wspolne przerwy dla maszyn?
	int n, m, maxDl, minDl; //n-liczba elenentow, m-liczba przerw, maxDl- max dlugosc zadania, minDl - minimalna dlugosc zadania
public:
	Ant();
	Ant(int n);
	~Ant();

	void generateInst(int max, int min);
	void generateBreaks();
};

