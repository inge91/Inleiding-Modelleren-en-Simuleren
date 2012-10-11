import random
import time
import sys
from termcolor import colored

random.seed(0)

# Enums for communication between board and cell class
SUSHU = 1
INFHU = 2
IMMHU = 3
SUSMO = 4
INFMO = 5

class board:

    world = []

    def __init__(self, size_x, size_y, n_susceptible_humans, n_infected_humans,
            n_immune_humans, n_uninfected_mosquitoes,  n_infected_mosquitoes):

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
        coords = self.__fill_elements(n_uninfected_mosquitoes, SUSMO, available_positions)
        coords = self.__fill_elements(n_infected_mosquitoes, INFMO, available_positions)

    def print_world(self):
        for j in xrange(0, self.size_y):
            for i in xrange(0,self.size_x ):
                if (len(self.world[j][i].get_elements()) == 0):
                    print "0",
                else:
                    elements = self.world[j][i].get_elements()
                    # in case of one object on a cell
                    if(len(elements) == 1):
                        if SUSHU in elements:
                            print colored("o", "magenta"),
                        elif INFHU in elements:
                            print colored("o", "green"),
                        elif IMMHU in elements:
                            print colored("o", "yellow"),
                        elif SUSMO in elements:
                            print colored("m", "blue"),
                        elif INFMO in elements:
                            print colored("m", "red"),
                    else:
                        if INFHU in elements and SUSMO in elements:
                            print colored("x", "red"),
                        elif SUSHU in elements and INFMO in elements:
                            print colored("x", "green"),
                        elif SUSHU in elements and SUSMO in elements:
                            print colored("x", "yellow"),
                        elif INFHU in elements and INFMO in elements:
                            print colored("x", "magenta"),
                        elif IMMHU in elements:
                            print colored("x", "cyan"),

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
            self.world[y][x].set_element(name)
            del coords[rand_val]
        return coords 
    
    # Returns a list of coordinates of where to find members of population name
    def __get_position(self, name):
        coords = []
        for y in xrange(0, self.size_y):
            for x in xrange(0, self.size_x):
                if(name in self.world[y][x].get_elements()):
                    coords.append((x,y))
        return coords

    # Returns a list of possible coordinates:
    #############TODO: Make world torus? #########################
    # -Not over the edge
    # -Not multiple mosquitoes same place 
    def __possible_coords(self, coord, impossible_coords):
        possible_coords = [] 
        x = coord[0]
        y = coord[1]

        # Check left
        if( (x - 1 > -1) and ((x - 1, y) not in impossible_coords)):
            possible_coords.append((x - 1, y))

        # Check right
        if((x + 1 < self.size_x) and ((x + 1, y) not in impossible_coords)):
            possible_coords.append((x + 1, y))
        
        # Check up
        if((y - 1 > -1) and ((x, y - 1) not in impossible_coords)):
            possible_coords.append((x, y - 1))

        # Check down
        
        if( (y + 1 < self.size_y) and ((x, y + 1) not in impossible_coords)):
            possible_coords.append((x, y + 1))

        return possible_coords
        

    # makes a mosquito move to new position
    def __move_mosquito(self, coord, impossible_coords):
        possible_coords = self.__possible_coords(coord, impossible_coords)
        if len(possible_coords) == 0:
            return [] 
        else: 
            i = random.randint(0, len(possible_coords) - 1)
            new_coord = possible_coords[i]
            x = new_coord[0]
            y = new_coord[1]
            if( INFMO in  self.world[coord[1]][coord[0]].get_elements()):
                mosquito_kind = INFMO
            else:
                mosquito_kind = SUSMO

            objects = self.world[coord[1]][coord[0]].get_objects()
            for element in objects:
                if isinstance(element, Mosquito):
                    self.world[y][x].add_object(element)
                    break
            self.world[coord[1]][coord[0]].remove_element(mosquito_kind)

        return [(x, y)]

          
    # Mosquitoes make a random step
    def __move_mosquitoes(self):
        temp_list = []
        # Let all mosquitoes move
        for i in self.all_mosquitoes:
            temp_list += self.__move_mosquito(i, temp_list)
        self.all_mosquitoes = temp_list

    # all occupied cells are getting updated
    def __update_population(self):
        all_coords = list(set( self.all_mosquitoes +  self.all_humans))
        for (x, y) in all_coords:
            self.world[y][x].update_elements()

    # The mosquitos go and bite
    # Two possibilities that change things:
    #   - Infected human gets bitten by uninfected mosquito. Mosquito gets
    #   infected
    #   - uninfected human gets bitten by infected mosquito. Human gets
    #   infected.
    def __mosquito_bites(self):
        # Make an intersection of all_humans and all_mosquitos
        human_and_mosquito = list(set(self.all_mosquitoes) & set(self.all_humans))
        
        # Check all cells with both a human and a mosquito
        for coord in human_and_mosquito:
            objects = self.world[coord[1]][coord[0]].get_objects()
            if(isinstance(objects[0], Mosquito)):  
                if(objects[0].is_hungry()):
                    if(objects[1].get_state() == INFHU and
                             objects[0].get_state() == SUSMO):
                         ## Remove mosquito and add infected moso
                         objects[0].set_state(INFMO)
                         objects[0].set_hunger()
                         ## (No longer hungT)
                    elif(objects[1].get_state() == SUSHU and
                            objects[0].get_state() == INFMO):
                         ## Remove human state and add infected human
                         objects[1].set_state(INFHU)
                         objects[0].set_hunger()
                    else:
                        continue
                else:
                    continue
                # in case first element is the human
            else:
                if(objects[1].is_hungry()):
                    if(objects[0].get_state() == INFHU and
                            objects[1].get_state() == SUSMO):
                        ## Remove mosquito and add infected mosquito
                         objects[1].set_state(INFMO)
                         objects[1].set_hunger()
                    elif(objects[0].get_state() == SUSHU and
                            objects[1].get_state() == INFMO):
                        ## Remove human state and add infected human
                        objects[0].set_state(INFHU)
                        objects[1].set_hunger()
                    else:
                        continue
                else:
                    continue


    # Remove dead people from the world and all_human list
    def __cleanup_bodies(self):
        new_humans = []
        for coord in self.all_humans:
            objects = self.world[coord[1]][coord[0]].get_objects()
            for i in objects:
                if isinstance(i, Human):
                    # In case the human is dead remove him from the field
                    # And add new uninfected human
                    if i.is_dead():
                        # Store the mosquito temporary
                        self.all_humans.remove(coord)
                        self.world[coord[1]][coord[0]] = Cell()
                        #create new cell and add mosquito
                        for i in objects:
                            if isinstance(i, Mosquito):
                                self.world[coord[1]][coord[0]].add_object(i)
                                break
                        new_humans += self.__spawn_human(new_humans)
        self.all_humans += new_humans
    
    # Spawns a new human next to an already existing human
    def __spawn_human(self, new_humans):
        while(True):

            forbidden = self.all_humans + new_humans
            # Choose a random person to cling to
            var = random.randint(0, len(self.all_humans)-1)
            person = self.all_humans[var]
            x = person[0]
            y = person[1]

            possible_coords = [] 
            # Check left
            if( (x - 1 > -1) and ((x - 1, y) not in forbidden)):
                possible_coords.append((x - 1, y))

            # Check right
            if((x + 1 < self.size_x) and ((x + 1, y) not in forbidden)):
                possible_coords.append((x + 1, y))
            
            # Check up
            if((y - 1 > -1) and ((x, y - 1) not in forbidden)):
                possible_coords.append((x, y - 1))

            # Check down
            if( (y + 1 < self.size_y) and ((x, y + 1) not in forbidden)):
                possible_coords.append((x, y + 1))
            
            if(len(possible_coords) == 0):
                continue
            else:
                rand = random.randint(0, len(possible_coords)-1)
                newcoord = possible_coords[rand]
                break
        # TODO possible to add sick or anything?
        self.world[newcoord[1]][newcoord[0]].set_element(SUSHU)
        return [newcoord]

    # The simulation loop that runs 
    def run(self):
        mosquit1 = self.__get_position(SUSMO)
        mosquit2 = self.__get_position(INFMO)
        # create field that keeps track of all mosquitoes
        self.all_mosquitoes = mosquit1 + mosquit2
        human1 = self.__get_position(SUSHU)
        human2 = self.__get_position(INFHU)
        human3 = self.__get_position(IMMHU)
        # do the same for all humans
        self.all_humans = human1 + human2 + human3
        i = 0 
        
        while(True):
            print i
            self.__move_mosquitoes()
            # make mosquitoes hungry and change the state of people
            self.__update_population()    
            self.__cleanup_bodies()
            # let mosquito bite
            self.__mosquito_bites()
            print "\n" 
            self.print_world()        
            i+=1
            objects = self.world[2][2].get_objects()
            if len(objects) > 1:
                   if isinstance(objects[0], Mosquito) and isinstance(objects[1], Mosquito):
                       print "help"
            raw_input("Press Enter to continue...\n")




# Class for every cell of the world
class Cell:

    def __init__(self):
        self.occupants = []

    # Return the list of objects
    def get_objects(self):
        return self.occupants
    
    # Get list of enums
    def get_elements(self):
        enum_list = []
        for i in self.occupants:
            enum_list.append(i.get_state())
        return enum_list

    # Add some kind of instance to a cell
    # and returns its content
    def set_element(self, element):
        if(element == SUSHU or element == INFHU or element == IMMHU):
            self.occupants.append(Human(element))
        elif(element == SUSMO or element == INFMO):
                self.occupants.append(Mosquito(element))
        else:
            print "The element " + element + " is not recognized."  
            sys.exit(1)
        return self.occupants

    # Remove an instance from the cell
    def remove_element(self, element):
        if(element == SUSHU or element == INFHU or element == IMMHU):
            for i in xrange(0, len(self.occupants)):
                if isinstance(self.occupants[i], Human):
                    del self.occupants[i]
                    break
        elif(element == SUSMO or element == INFMO):
            for i in xrange(0, len(self.occupants)):
                if isinstance(self.occupants[i], Mosquito):
                    del self.occupants[i]
                    break
        else:
            sys.exit(1)
        return self.occupants
    
    # Adds an object to occupants
    def add_object(self, element):
        self.occupants.append(element)
        return self.occupants

    # Update that needs to happen for every iteration
    def update_elements(self):
        for i in xrange(0, len(self.occupants)):
            self.occupants[i].update()


# Class for a mosquito instance
# States can be: SUSMO or INFMO
# TODO: Add amount of days not hungry tracker and maybe let them die?
class Mosquito:
    def __init__(self, state):
        self.state = state
        self.hungry = True
        self.count_hungry = 0

    def set_state(self, state):
        self.state = state
    
    def set_hunger(self):
        if(self.hungry):
            self.hungry = False
            self.count_hungry = 0
        else:
            self.hungry = True

    def is_hungry(self):
        return self.hungry

    def get_state(self):
        return self.state
    
    def update(self):
        if self.hungry:
            pass
        elif self.count_hungry == 2:
            self.hungry = True
            self.count_hungry = 0
        else:
            self.count_hungry += 1


# Class for a human instance
class Human:
    def __init__(self, state):
        self.state = state
        self.dead = False
    
    def set_state(self, state):
        self.state = state

    def get_state(self):
        return self.state

    def is_dead(self):
        if(self.dead):
            return True
        else: 
            return False
    
    # Updates the state of the human
    def update(self):
        # If a human is suceptible
        if self.state == SUSHU:
            var = random.randint(0,20)
            if(var == 1):
                self.dead = True
        # possibility of death and of susc
        # and immunity
        elif self.state == INFHU:
            var = random.randint(0, 10)
            if(var < 1):
                self.dead = True
            elif(var == 4):
                self.state = SUSHU
            elif(var == 9 ):
                self.state = IMMHU
        elif self.state == IMMHU:
            var = random.randint(0,20)
            if(var<4):
                self.state = SUSHU
            if(var == 5):
                self.dead = True
            



def main():
    my_board = board(40,40, 200, 300, 0, 80,0)
    my_board.print_world()
    my_board.run()
    print "\n" 
    my_board.print_world()

if __name__ == "__main__":
    main()

            


        

        



