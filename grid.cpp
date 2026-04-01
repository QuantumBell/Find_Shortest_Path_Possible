#include "Grid.h"
#include <iostream>
#include <random>
#include <ctime>
#include <queue>
#include <thread>
#include <chrono>


Grid::Grid(int rows, int cols) : m_rows(rows), m_cols(cols) {
    m_data.resize(rows, std::vector<char>(cols, '.'));
}

void Grid::setWall(int r, int c) {
    for (int i{ 0 }; i < r; i++) {
        for (int j{ 0 }; j < c; j++) {

            if (rand() % 100 < 23) {
                m_data[i][j] = '#';
            }

            else {
                m_data[i][j] = '.';
            }
        }
    }
}

void Grid::display() {
    for (const auto& row : m_data) {
        for (const auto& cell : row) {
            std::cout << cell << " ";
        }
        std::cout << '\n';
    }
}

void Grid::setGoal() {

    m_goalSide = rand() % 4;

    switch (m_goalSide) {
    case 0:
        m_goalCol = 0;
        m_goalRow = rand() % m_rows;
        break;
    case 1:
        m_goalCol = rand() % m_cols;
        m_goalRow = 0;
        break;
    case 2:
        m_goalCol = m_cols - 1;
        m_goalRow = rand() % m_rows;
        break;
    case 3:
        m_goalCol = rand() % m_cols;
        m_goalRow = m_rows - 1;
        break;
    }

    m_data[m_goalRow][m_goalCol] = 'G';

}

void Grid::setStart() { // ne
    
    m_startSide = rand() % 4;

    while (std::abs(m_startSide - m_goalSide) != 2) {
        m_startSide = rand() % 4;
    }

    switch (m_startSide) {
    case 0:
        m_startCol = 0;
        m_startRow = rand() % m_rows;
        break;
    case 1:
        m_startCol = rand() % m_cols;
        m_startRow = 0;
        break;
    case 2:
        m_startCol = m_cols - 1;
        m_startRow = rand() % m_rows;
        break;
    case 3:
        m_startCol = rand() % m_cols;
        m_startRow = m_rows - 1;
        break;
    }

    m_data[m_startRow][m_startCol] = 'S';
}

bool Grid::findPath() {
    std::queue<std::pair<int, int>> q;
    bool goalFound = false;
    bool visited[100][100] = { false };
    std::pair<int, int> parent[100][100];

    q.push({ m_startRow, m_startCol });

    visited[m_startRow][m_startCol] = true;
    
    while (!q.empty() && !goalFound) {

        std::pair<int, int> current = q.front();
        int r = current.first;
        int c = current.second;

        if ( r < m_rows -1) {
            char neighbor = m_data[r + 1][c];
            if (neighbor == 'G') {
                parent[r + 1][c] = { r,c };
                goalFound = true;
            }
            else if (neighbor == '.') {
                if (!visited[r + 1][c]) {
                    visited[r + 1][c] = true;
                    parent[r + 1][c] = { r,c };
                   // m_data[r + 1][c] = 'x';
                    q.push({ r + 1, c });
                }
            }
        }

        if ( c < m_cols - 1) {
            char neighbor = m_data[r][c + 1];
            if (neighbor == 'G') {
                parent[r][c + 1] = { r,c };
                goalFound = true; 
            }
            else if (neighbor == '.') {
                if (!visited[r][c + 1]) {
                    visited[r][c + 1] = true;
                    parent[r][c + 1] = { r,c };
                   // m_data[r][c + 1] = 'x';
                    q.push({ r, c + 1 });
                }
            }
        }

        if ( r > 0) {
            char neighbor = m_data[r - 1][c];
            if (neighbor == 'G') {
                parent[r - 1][c] = { r,c };
                goalFound = true;
            }
            else if (neighbor == '.') {
                if (!visited[r - 1][c]) {
                    visited[r - 1][c] = true;
                    parent[r - 1][c] = { r,c };
                    //m_data[r - 1][c] = 'x';
                    q.push({ r - 1, c });
                }
            }
        }

        if ( c > 0 ){
            char neighbor = m_data[r][c - 1];
            if (neighbor == 'G') {
                parent[r][c - 1] = { r,c };
                goalFound = true;
            }
            else if (neighbor == '.') {
                if (!visited[r][c - 1]) {
                    visited[r][c - 1] = true;
                    parent[r][c - 1] = { r , c };
                    //m_data[r][c - 1] = 'x';
                    q.push({ r, c - 1 });
                }
            }
        }

        q.pop();

        
    }

    if (goalFound) {
        std::pair<int, int> curr = { m_goalRow, m_goalCol };
        std::vector < std::pair<int, int>> path;


        while (curr != std::make_pair(m_startRow, m_startCol)) {
            path.push_back(curr);
            curr = parent[curr.first][curr.second];
        }

        for (size_t i{ path.size() }; i > 0; i--) {
                int r = path[i - 1].first;
                int c = path[i - 1].second;

                if (m_data[r][c] != 'G' && m_data[r][c] != 'S') {
                    m_data[r][c] = 'x';

                    std::cout << "\033[H" << std::flush;
                    display();
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));



                }
            }
            return true;
        }

        return false;



    }



void Grid::clear() {
    for (int i{ 0 }; i < m_rows; i++) {
        for (int j{ 0 }; j < m_cols; j++) {
            m_data[i][j] = '.';
        }
    }
}
