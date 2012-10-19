CXX = g++
CFLAGS = -O3 -std=c++11

default: forestfire graphical sdl

forestfire: Simulation.cpp SimulationField.cpp test.cpp
	$(CXX) $(CFLAGS) -o forestfire Simulation.cpp SimulationField.cpp test.cpp

graphical: Simulation.cpp SimulationField.cpp test_graphical.cpp
	$(CXX) $(CFLAGS) -o forestfire_g Simulation.cpp SimulationField.cpp test_graphical.cpp

sdl: Simulation.cpp SimulationField.cpp test_sdl.cpp
	$(CXX) $(CFLAGS) $(shell pkg-config --cflags --libs sdl) -o forestfire_sdl Simulation.cpp SimulationField.cpp test_sdl.cpp

clean:
	rm forestfire forestfire_g forestfire_sdl

