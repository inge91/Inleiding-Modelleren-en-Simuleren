#include "SimulationField.h"
#include "Simulation.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, const char *argv[])
{
    //vector<int> sizes = {5, 10, 15, 20};
    //vector<double> densities = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8};
    vector<int> sizes = {20};
    vector<double> densities = {0.8};

    // save the data
    ofstream file("data.txt");

    for (int &size : sizes) {
        for (double &density : densities) {
            cout << "Size: " << size << endl;
            cout << "Density: " << density << endl << endl;

            Simulation s(size, size, density);
            SimulationResult result = s.run();

            file << size << ", " << density << ", " << result.other_side_reached
                 << ", " << result.steps_to_other_side << ", "
                 << result.percentage_burnt << endl;
        }
    }

    file.close();

    return 0;
}
