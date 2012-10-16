#!/usr/bin/env python
# encoding: utf-8

from pylab import *
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

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
hexbin(densities, reached, gridsize=30, mincnt=1)
cb = colorbar()
cb.set_label("amount of data points")
xlabel("vegetation density")
ylabel("Other side reached (boolean)")
xlim(0, 1)
ylim(-0.05, 1.05)
savefig("density_vs_reached.png")
clf()

# now plot the density against how many steps it took to the other side
hexbin(densities, steps, gridsize=30, mincnt=1)
cb = colorbar()
cb.set_label("amount of data points")
xlabel("vegetation density")
ylabel("Number of steps to other side (0 = not reached)")
xlim(0, 1)
savefig("density_vs_steps.png")
clf()

# now the same except with the percentage of burnt vegetation
hexbin(densities, burnt, gridsize=30, mincnt=1)
cb = colorbar()
cb.set_label("amount of data points")
xlabel("vegetation density")
ylabel("% of vegetation that was burnt")

xlim(0, 1)
ylim(0, 102)
savefig("density_vs_burnt.png")
clf()

# sizes against number of steps

# filter the lists to only plot the densities from 0.6 to 0.9
szs = [size for (size, density) in zip(sizes, densities) if 0.6 <= density <= 0.9]
sts = [step for (step, density) in zip(steps, densities) if 0.6 <= density <= 0.9]
hexbin(szs, sts, gridsize=30, mincnt=1)
cb = colorbar()
cb.set_label("amount of data points")
xlabel("size")
ylabel("Steps to reach other side")

savefig("size_vs_steps.png")
clf()
