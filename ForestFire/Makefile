CXX = g++
CFLAGS = -O3 -std=c++11
BIN = forestfire

default: forestfire graphical

forestfire: Simulation.cpp SimulationField.cpp test.cpp
	$(CXX) $(CFLAGS) -o $(BIN) Simulation.cpp SimulationField.cpp test.cpp

graphical: Simulation.cpp SimulationField.cpp test_graphical.cpp
	$(CXX) $(CFLAGS) -o forestfire_g Simulation.cpp SimulationField.cpp test_graphical.cpp

clean:
	rm $(BIN) forestfire_g
