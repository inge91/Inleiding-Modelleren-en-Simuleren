#!/usr/bin/env python
# encoding: utf-8

from pylab import *

# columns in the data correspond to:
# size | density | other side reached (boolean) | steps to other side (0 if not
# reached) | percentage burnt
data = loadtxt("data.txt", delimiter=",")

sizes     = data[:, 0]
densities = data[:, 1]
reached   = data[:, 2]
steps     = data[:, 3]
burnt     = data[:, 4]

# first plot the density against whether the other side has been reached
scatter(densities, reached)
savefig("density_vs_reached.png")
xlabel("vegetation density")
ylabel("Other side reached (boolean)")
clf()

# now plot the density against how many steps it took to the other side
hexbin(densities, steps, gridsize=30, mincnt=1)
cb = colorbar()
cb.set_label("amount of data points")
savefig("density_vs_steps.png")
xlabel("vegetation density")
ylabel("Number of steps to other side (0 = not reached)")
clf()

# now the same except with the percentage of burnt vegetation
hexbin(densities, burnt, gridsize=30, mincnt=1)
cb = colorbar()
cb.set_label("amount of data points")
xlabel("vegetation density")
ylabel("% of vegetation that was burnt")

xlim(0, 0.95)
ylim(0, 102)
savefig("density_vs_burnt.png")
clf()
