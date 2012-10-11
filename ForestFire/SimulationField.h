#ifndef SIMULATION_FIELD_H
#define SIMULATION_FIELD_H

#include <vector>

struct Point
{
    Point(int xx, int yy)
    {
        x = xx;
        y = yy;
    }

    bool operator<(const Point &rhs) const
    {
        return (x < rhs.x);
    }

    bool operator==(const Point &rhs) const
    {
        return (x == rhs.x) && (y == rhs.y);
    }

    int x;
    int y;
};

enum CellType {
    EMPTY,
    VEGETATED,
    BURNING,
    BURNT
};

// A 2D array, implemented as array of row-arrays.
class SimulationField
{
    public:
        SimulationField(int x_size, int y_size, CellType initial_value=EMPTY);
        ~SimulationField();

        // prints the field prettily
        void pretty_print();

        // returns the element at (y, x)
        int get(int y, int x);

        // assign value to the element at (y, x)
        void set(int y, int x, CellType value);

        // return wether elem is contained in the given row (counted from the
        // top)
        bool contains(int row, CellType elem);

        // return the count of elem in the array
        int count(CellType elem);

        // the array's size (x and y)
        Point size;

    private:
        int *m_array;
        int m_x_size;
        int m_y_size;
};

#endif
