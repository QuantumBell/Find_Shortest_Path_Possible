#pragma once
#include <vector>

class Grid
{
private:

	int m_goalRow{};
	int m_goalCol{};
	int m_goalSide{};
	int m_startRow{};
	int m_startCol{};
	int m_startSide{};
	int m_rows{};
	int m_cols{};
	std::vector<std::vector<char>> m_data{};

public:

	Grid(int rows, int cols);
	void setWall(int r, int c);
	void setGoal();
	void setStart();
	void display();
	bool findPath();
	void clear();

	//void calcDist();
	

};



