#include "SimulationField.h"
#include <iostream>
#include <ctime>

using namespace std;

SimulationField::SimulationField(int x_size, int y_size, CellType initial_value)
    : size(x_size, y_size), m_x_size(x_size), m_y_size(y_size)
{
    m_array = new int[x_size * y_size];
}

SimulationField::~SimulationField()
{
    delete [] m_array;
}

int SimulationField::get(int y, int x)
{
    return m_array[x + y * m_x_size];
}

void SimulationField::set(int y, int x, CellType value)
{
    m_array[x + y * m_x_size] = value;
}

void SimulationField::pretty_print()
{
    for (int y = 0; y < m_y_size; ++y) {
        for (int x = 0; x < m_x_size; ++x) {
            cout << get(y, x) << " ";
        }

        cout << endl;
    }
}

bool SimulationField::contains(int row, CellType elem)
{
    for (int i = 0; i < m_x_size; ++i) {
        if (get(row, i) == elem)
            return true;
    }

    return false;
}

int SimulationField::count(CellType elem)
{
    int count = 0;

    for (int i = 0; i < m_x_size * m_y_size; ++i) {
        if (m_array[i] == elem) {
            count += 1;
        }
    }

    return count;
}
