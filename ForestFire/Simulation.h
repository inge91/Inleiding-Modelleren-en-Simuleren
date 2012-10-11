#ifndef SIMULATION_H
#define SIMULATION_H

#include "SimulationField.h"

#include <vector>
#include <map>

using namespace std;

// a struct to hold benchmarking information
struct SimulationResult
{
    bool other_side_reached;
    int steps_to_other_side;
    double percentage_burnt;
};

class Simulation
{
    public:
        Simulation(int x_size, int y_size, double veggie_density);
        ~Simulation();

        // pretty prints the field
        void pretty_print();

        // performs one simulation step
        void step();

        // runs an entire simulation
        SimulationResult run();

        // runs an entire simulation with pretty output
        void run_graphical(double delay=0.5);

    private:
        // initializes the field
        void initialize_field(double veggie_density);

        // lights a cell on fire
        void set_burning(int x, int y);

        // returns the neighbours of a point that will burn in the next timestep
        void burning_neighbours(int x, int y, vector<Point> &will_burn);

        // the underlying field class
        SimulationField m_field;

        // vector of burning cells
        vector<Point> m_burning;
};

#endif
