#include "Simulation.h"
#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <ctime>
#include <algorithm>

using namespace std;

Simulation::Simulation(int x_size, int y_size, double veggie_density)
    : m_field(x_size, y_size), m_burning()
{
    initialize_field(veggie_density);
}

Simulation::~Simulation()
{
}

void Simulation::initialize_field(double veggie_density)
{
    // seed the RNG
    srand(time(NULL));

    // loop through the entire field, and assign each cell a $(veggie_density)
    // chance of becoming vegetated
    for (int y = 0; y < m_field.size.y; ++y) {
        for (int x = 0; x < m_field.size.x; ++x) {
            double r = static_cast<double>(rand()) / RAND_MAX;

            if (r < veggie_density) {
                m_field.set(y, x, VEGETATED);
            }
        }
    }

    // now light the bottom row on fire
    for (int x = 0; x < m_field.size.x; ++x) {
        set_burning(x, m_field.size.y - 1);
    }
}

void Simulation::set_burning(int x, int y)
{
    // set the cell at (x, y) to burning and add it to the list of burning cells
    m_field.set(y, x, BURNING);
    m_burning.push_back(Point(x, y));
}

void Simulation::burning_neighbours(int x, int y, vector<Point> &will_burn)
{
    // do nothing if the given cell is not burning
    if (m_field.get(y, x) != BURNING) {
        return;
    }

    int x_max = m_field.size.x;
    int y_max = m_field.size.y;

    // loop through the 8-cell Moore neighbourhood plus the original cell
    for (int x_offset = -1; x_offset <= 1; ++x_offset) {
        for (int y_offset = -1; y_offset <= 1; ++y_offset) {
            int new_x = x + x_offset;
            int new_y = y + y_offset;

            // check if the cell is not out of bounds and is vegetated
            // if these conditions are true, it will burn
            if (   new_x < x_max
                && new_x >= 0
                && new_y < y_max
                && new_y >= 0
                && m_field.get(new_y, new_x) == VEGETATED)
            {
                will_burn.push_back(Point(new_x, new_y));
            }
        }
    }

    return;
}

void Simulation::step()
{
    // first look at which cells will start burning

    // will hold all the future burning cells
    vector<Point> burning_next;
    // used to get data from burning_neighbours()
    vector<Point> will_burn;

    for (Point p : m_burning) {
        burning_neighbours(p.x, p.y, will_burn);

        // add each of the current point's neighbours to burning_next and remove
        // them from will_burn
        while (!will_burn.empty()) {

            // make sure the cell hasn't already been added
            auto found = find(burning_next.begin(), burning_next.end(),
                              will_burn.back());

            if (found != burning_next.end()) {
                burning_next.push_back( will_burn.back() );
                will_burn.pop_back();
            }
        }
    }

    // make the old burning cells burnt, ignite the new ones, and replace the
    // vector of burning cells
    for (Point &p : m_burning) {
        m_field.set(p.y, p.x, BURNT);
    }

    for (Point &p : burning_next) {
        m_field.set(p.y, p.x, BURNING);
    }

    m_burning.clear();

    // copy the values from burning_next to m_burning
    for (auto elem = burning_next.begin(); elem != burning_next.end(); elem++) {
        m_burning.push_back(*elem);
    }
}

SimulationResult Simulation::run()
{
    // Runs the simulation until nothing changes anymore.
    // Returns an object indicating how many steps it took for the fire to reach
    // the other side (0 = not reached) and which percentage of the vegetation
    // has been burned.

    int steps = 0;
    SimulationResult result;

    int initial_vegetation = m_field.count(VEGETATED);

    while (!m_burning.empty()) {
        step();
        steps += 1;

        // check whether the other side has been reached yet
        if (m_field.contains(0, BURNT)) {
            result.other_side_reached = true;
            result.steps_to_other_side = steps;
        }
    }

    // check how much vegetation has been burnt
    double final_vegetation = m_field.count(VEGETATED);
    double burn_percentage = ((initial_vegetation - final_vegetation)
                             / (double)initial_vegetation) * 100;

    result.percentage_burnt = burn_percentage;

    return result;
}

void Simulation::run_graphical(double delay)
{
    while (!m_burning.empty()) {
        pretty_print();
        step();
        sleep(delay);
        cout << endl;
    }

    pretty_print();
}

void Simulation::pretty_print()
{
    m_field.pretty_print();
}
