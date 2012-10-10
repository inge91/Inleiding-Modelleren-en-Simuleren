import random


SUSHU = 1
INFHU = 2
IMMHU = 3
SUSMU = 4
INFMU = 5

class board:

    world = []

    def __init__(self, size_x, size_y, n_susceptible_humans, n_infected_humans,
            n_immune_humans, n_uninfected_musquitoes,  n_infected_musquitoes):

        # Create an empty 2D list that creates all elements
        self.world = [[Cell() for _ in xrange(size_x)] for _ in xrange(size_y)]
        self.size_x = size_x
        self.size_y = size_y

        available_positions = []
        # Add all the possible positions to a list and choose random 
        for i in xrange(0, size_x):
            for j in xrange(0, size_y):
                available_positions.append((i,j))

        # Choose a random initial position for the susceptible humans  
        coords = self.__fill_elements(n_susceptible_humans, SUSHU, available_positions)
        coords = self.__fill_elements(n_infected_humans, INFHU, available_positions)
        coords = self.__fill_elements(n_immune_humans, IMMHU, available_positions)
        coords = self.__fill_elements(n_uninfected_musquitoes, SUSMU, available_positions)
        coords = self.__fill_elements(n_infected_musquitoes, INFMU, available_positions)

    def print_world(self):
        for i in xrange(0,self.size_x ):
            for j in xrange(0, self.size_y):
                if (len(self.world[i][j].get_elements()) == 0):
                    print "0",
                else:
                    print self.world[i][j].get_elements()[0],
            print "\n",
            

    # Fills world with a population and returns new list of available
    # coordinates
    def __fill_elements(self, n_population, name, coords):
        """ world gets filled with the amount of n_population while
            the coordinate list shrinks until it only contains empty spaces"""
        for elements in xrange(0, n_population):
            rand_val = random.randint(0, len(coords)-1)
            coord = coords[rand_val]
            x = coord[0]
            y = coord[1]
            self.world[x][y].set_element(name)
            del coords[rand_val]
        return coords 
    
    # Returns a list of coordinates of where to find members of population name
    def __get_position(self, name):
        coords = []
        for i in xrange(0, self.size_x-1):
            for j in xrange(0, self.size_y-1):
                if(name in self.world[i][j].get_elements):
                    coords.append((i,j))
        return coords

    # Returns a list of possible coordinates:
    #############TODO: Make world torus #########################
    # -Not over the edge
    # -Not multiple musquitoes same place 
    def __possible_coords(self, coord, all_musquitoes):
        possible_coords = [] 
        x = coord[0]
        y = coord[1]

        # Check left
        if(x - 1 > 0 and (x - 1, y) not in all_musquitoes):
            possible_coords.append((x - 1, y))

        # Check right
        if(x + 1 > self.size_x and (x + 1, y) not in all_musquitoes):
            possible_coords.append((x + 1, y))
        
        # Check up
        if( y - 1 > 0 and (x, y - 1) not in all_musquitoes):
            possible_coords.append((x, y - 1))

        # Check down
        if( y + 1 > self.size_y and (x, y + 1) not in all_musquitoes):
            possible_coords.append()

        return possible_coords
        

    # makes a musquito move to new position
    def __move_musquito(self, coord, all_musquitoes):
        possible_coords = __possible_coords(coord, all_musquitoes)
        i = random.randint(0, len(possible_coords))
        new_coord = possible_coords[i]
        x = new_coord[0]
        y = new_coord[1]
        if( INFMU in  self.word[coord[1]][coord[2]].get_elements()):
            musquito_kind = INFMU
        else:
            musquito_kind = SUSMU

        self.world[x][y].set_element(musquito_kind)
        self.world[coord[1]][coord[2]].remove_element(musquito_kind)

          

    # make the musquitoes move in a random 
    def __move_musquitoes(self):
        musquit1 = self.__get_position(self.SUSMU)
        musquit2 = self.__get_position(self.INFMU)
        all_musquitoes = musquit1 + musquit2
        # Let all musquitoes move
        for i in all_musquitoes:
            self.__move_musquito(i, all_musquitoes)


    # The simulation loop that runs 
    def run():
        while(True):
            move_musquitoes()
            update_hunger()
            


# Class for every cell of the world
class Cell:

    def __init__(self):
        self.occupants = []

    def get_elements(self):
        return self.occupants

    # Add some kind of instance to a cell
    # and returns its content
    def set_element(self, element):
        self.occupants.append(element)
        return self.occupants
        

def main():
    my_board = board(10, 10, 3, 5, 8, 1, 7)
    my_board.print_world()

if __name__ == "__main__":
    main()

            


        

        



