#include "Simulation.h"
#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <ctime>
#include <algorithm>
#include <set>

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
            } else {
                m_field.set(y, x, EMPTY);
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
    if (m_field.get(y, x) == VEGETATED) {
        m_field.set(y, x, BURNING);
        m_burning.push_back(Point(x, y));
    }
}


void Simulation::future_burning(set<Point> &will_burn)
{
    // loop through the entire field to collect vegetated cells that border
    // burning ones
    for (int x = 0; x < m_field.size.x; ++x) {
        for (int y = 0; y < m_field.size.y; ++y) {
            if (m_field.get(y, x) == VEGETATED) {
                // check if any of its neighbours are burning
                if (next_to_fire(x, y)) {
                    will_burn.insert(Point(x, y));
                }
            }
        }
    }
}

bool Simulation::next_to_fire(int x, int y)
{
    int new_x, new_y;

    for (int x_offset = -1; x_offset <= 1; ++x_offset) {
        for (int y_offset = -1; y_offset <= 1; ++y_offset) {
            new_x = x + x_offset;
            new_y = y + y_offset;

            // make sure we're still inside the playing field, and not in the
            // original cell
            if (new_x < 0 || new_y < 0 || new_x >= m_field.size.x
                || new_y >= m_field.size.y || (x_offset == 0 && y_offset == 0)) {
                continue;
            }

            if (m_field.get(new_y, new_x) == BURNING) {
                return true;
            }
        }
    }

    return false;
}

void Simulation::step()
{
    // first look at which cells will start burning

    // used to hold the cells that will burn in the next iteration
    set<Point> will_burn;
    future_burning(will_burn);

    // make the old burning cells burnt, ignite the new ones, and replace the
    // vector of burning cells
    for (Point &p : m_burning) {
        m_field.set(p.y, p.x, BURNT);
    }


    // clear the old burning list
    m_burning.clear();

    //// copy the values from burning_next to m_burning
    //copy(will_burn.begin(), will_burn.end(), m_burning.begin());

    // ignite the new points
    for (auto &p : will_burn) {
        set_burning(p.x, p.y);
    }
}

SimulationResult Simulation::run()
{
    // Runs the simulation until nothing changes anymore.
    // Returns an object indicating how many steps it took for the fire to reach
    // the other side (0 = not reached) and which percentage of the vegetation
    // has been burned.

    int steps = 0;

    // initialize the result struct
    SimulationResult result;
    result.other_side_reached = false;
    result.steps_to_other_side = 0;

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

bool Simulation::running()
{
    return !m_burning.empty();
}

void Simulation::pretty_print()
{
    m_field.pretty_print();
}
