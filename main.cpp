#include <iostream>
#include "Grid.h"
#include <random>
#include <ctime>

int main() {

	srand(time(0));

	Grid grid{ 20, 20 };

	bool pathFound = false;
	do {
		
		grid.clear();
		grid.setWall(20, 20);
		grid.setGoal();
		grid.setStart();

		pathFound = grid.findPath();

	} while (!pathFound);

	system("CLS");

	grid.display();

	return 0;
}
