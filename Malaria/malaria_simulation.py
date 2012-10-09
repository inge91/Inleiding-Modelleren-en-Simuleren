import random
class board:

    # All possible cell values
    EMPTY = 0
    SUSHU = 1
    INFHU = 2
    IMMHU = 3
    SUSMU = 4
    INFMU = 5
    world = []
    size_x
    size_y

    def __init__(self, size_x, size_y, n_susceptible_humans, n_infected_humans,
            n_immune_humans, n_uninfected_musquitoes,  n_infected_musquitoes):

        # Create an empty 2D list that creates all elements
        self.world = [[self.EMPTY] * size_x for _ in xrange(size_y)]
        self.size_x = size_x
        self.size_y = size_y

        available_positions = []
        # Add all the possible positions to a list and choose random 
        for i in xrange(0, size_x):
            for j in xrange(0, size_y):
                available_positions.append((i,j))

        # Choose a random initial position for the susceptible humans  
        coords = self.__fill_elements(n_susceptible_humans, self.SUSHU, available_positions)
        coords = self.__fill_elements(n_infected_humans, self.INFHU, available_positions)
        coords = self.__fill_elements(n_immune_humans, self.IMMHU, available_positions)
        coords = self.__fill_elements(n_uninfected_musquitoes, self.SUSMU, available_positions)
        coords = self.__fill_elements(n_infected_musquitoes, self.INFMU, available_positions)

    def print_world(self):
        for i in self.world:
            print i

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
            self.world[x][y] = name
            del coords[rand_val]
        return coords 
    
    # Returns a list of coordinates of where to find members of population name
    def __get_position(self, name):
        coords = []
        for i in xrange(0, self.size_x-1):
            for j in xrange(0, self.size_y-1):
                if(self.world[i][j] == name):
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
        

    def __move_musquito(self, coord, all_musquitoes):
            __possible_coords(coord, all_musquitoes)

    # make the musquitoes move in a random 
    def __move_musquitoes(self):
        musquit1 = self.get_position(self.SUSMU)
        musquit2 = self.getposition(self.INFMU)
        all_musquitoes = musquit1 + musquit2
        # Let all musquitoes move
        for i in all_musquitoes:
            self.__move_musquito(i, all_musquitoes)


    # The simulation loop that runs 
    def run():
        while(True or not(all_dead())):
            move_musquitoes()
            update_hunger()
            

def main():
    my_board = board(10, 10, 3, 5, 8, 1, 7)
    print "hello"
    my_board.print_world()

if __name__ == "__main__":
    main()

            


        

        



