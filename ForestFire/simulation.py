from random import random
from termcolor import colored
from time import sleep
import os

class SimulationField():
    "A 2D array, implemented as list of row-lists. "

    def __init__(self, x_size, y_size, initial_value=0):
        """
        Parameters:
        x_size       : the width of the simulation field                                                            
        y_size       : the height of the simulation field                                                       
        initial_value: the value to initialize the array with
        """
        self.__field = [[initial_value] * x_size for _ in xrange(y_size)]
        self.size = (x_size, y_size)

    def pretty_print(self):
        """
        Pretty-print the array.
        """
        for row in self.__field:
            for elem in row:
                color = {
                    0: 'white',
                    1: 'green',
                    2: 'red',
                    3: 'grey'
                }[elem]
                print colored(elem, color),
            print '' # newline

    def __getitem__(self, indices):
        """
        Given a tuple (y, x), returns the corresponding element.
        """
        y, x = indices
        return self.__field[y][x]

    def __setitem__(self, indices, value):
        """
        Given a tuple (y, x), set the corresponding element.
        """
        y, x = indices
        self.__field[y][x] = value

    def __repr__(self):
        return str(self.__field)

class Simulation():
    """
    A forest fire simulation. The surface is a regular rectangle (not a 
    Pacman-style torus).

    Rules: There are 4 possible states; Empty, vegetated, burning, or burnt.
    - a burning cell will ignite every neighbouring cell in an 8-cell
      Moore-neighbourhood.
    - a burnt cell can not be ignited
    - after 1 step, a burning cell will turn into a burnt one

    Initially, the bottom row will be set on fire.
    """

    # cell constants
    EMPTY     = 0
    VEGETATED = 1
    BURNING   = 2
    BURNT     = 3

    def __init__(self, x_size, y_size, veggie_density=0.6):
        """ 
        Parameters:
        x_size: the width of the simulation field
        y_size: the height of the simulation field
        """

        self.__burning = []
        self.field = SimulationField(x_size, y_size, self.EMPTY)
        self.__initialize_field(veggie_density)

    def __initialize_field(self, veggie_density):
        "Initializes the field with a given vegetation density."

        # loop through the entire field, and assign each cell a $(veggie_density)
        # chance of becoming vegetated
        x_max, y_max = self.field.size
        for y in xrange(y_max):
            for x in xrange(x_max):
                # random returns a number between 0.0 and 1.0
                if random() <= veggie_density:
                    self.field[y, x] = self.VEGETATED

        # now light the bottom row on fire
        for x in xrange(x_max):
            self.__set_burning(x, y_max - 1)

    def __set_burning(self, x, y):
        """
        Sets cell (x, y) to BURNING and add its coordinates to the list of
        burning cells.
        """

        self.field[y, x] = self.BURNING
        self.__burning.append( (x, y) )

    def __burning_neighbours(self, coords):
        "Returns the neighbours of a cell that will burn in the next step"
        x, y = coords
        x_max, y_max = self.field.size

        will_burn = []
        # return an empty list if the given cell is not burning
        if self.field[y, x] != self.BURNING:
            return will_burn

        # loop through the 8-cell Moore neighbourhood plus the original cell
        for y_offset in [-1, 0, 1]:
            for x_offset in [-1, 0, 1]:
                # ignore the original cell
                if y_offset == x_offset == 0:
                    continue

                new_x = x + x_offset
                new_y = y + y_offset

                # check if the cell is not out of bounds and is vegetated
                # if it is, add it to the list of cells that will burn
                if (0 <= new_x < x_max) and (0 <= new_y < y_max):
                    if self.field[new_y, new_x] == self.VEGETATED:
                        will_burn.append( (new_x, new_y) )

        return will_burn

    def step(self):
        "Performs one simulation step"

        # first look at which cells will start burning
        burning_next = [self.__burning_neighbours(cell) for cell in self.__burning]

        # make the old burning cells barren and ignite the new burning cells
        for x, y in self.__burning:
            self.field[y, x] = self.BURNT

        self.__burning = []

        for b in burning_next:
            for (x, y) in b:
                self.__set_burning(x, y)

    def run(self, n, delay=0.5):
        "Runs the simulation for the specified amount of steps"
        for _ in xrange(n):
            os.system('clear')
            self.field.pretty_print()
            self.step()
            sleep(delay)

        self.field.pretty_print()