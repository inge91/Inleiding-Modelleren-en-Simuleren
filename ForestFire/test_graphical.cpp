#include "SimulationField.h"
#include "Simulation.h"
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    int size;
    double density;

    cout << "What is the field size (n x n)?" << endl << "> " << flush;
    cin >> size;

    cout << "What is the veggie density?" << endl << "> " << flush;
    cin >> density;

    Simulation s(size, size, density);
    s.run_graphical();

    return 0;
}
